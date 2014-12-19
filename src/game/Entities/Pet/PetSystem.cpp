#include "stdafx.h"
#include "utils.h"
#include "vector.h"
#include "char.h"
#include "sectree_manager.h"
#include "char_manager.h"
#include "mob_manager.h"
#include "PetSystem.h"
#include "common/VnumHelper.h"
#include "packet.h"
#include "item_manager.h"
#include "item.h"


extern int passes_per_sec;
EVENTINFO(petsystem_event_info)
{
	CPetSystem* pPetSystem;
};

// PetSystemА» update ЗШБЦґВ event.
// PetSystemАє CHRACTER_MANAGERїЎј­ ±вБё FSMАё·О update ЗШБЦґВ ±вБё chractersїН ґЮё®,
// OwnerАЗ STATEё¦ update ЗТ ¶§ _UpdateFollowAI ЗФјц·О update ЗШБШґЩ.
// ±Ч·±µҐ ownerАЗ stateё¦ updateё¦ CHRACTER_MANAGERїЎј­ ЗШБЦ±в ¶§№®їЎ,
// petsystemА» updateЗПґЩ°Ў petА» unsummonЗПґВ єОєРїЎј­ №®Б¦°Ў »э°еґЩ.
// (CHRACTER_MANAGERїЎј­ update ЗПёй chracter destroy°Ў pendingµЗѕо, CPetSystemїЎј­ґВ dangling ЖчАОЕНё¦ °ЎБц°н АЦ°Ф µИґЩ.)
// µы¶уј­ PetSystemёё ѕчµҐАМЖ® ЗШБЦґВ eventё¦ №Я»эЅГЕґ.
EVENTFUNC(petsystem_update_event)
{
	petsystem_event_info* info = dynamic_cast<petsystem_event_info*>( event->info );
	if ( info == NULL )
	{
		sys_err( "check_speedhack_event> <Factor> Null pointer" );
		return 0;
	}

	CPetSystem*	pPetSystem = info->pPetSystem;

	if (NULL == pPetSystem)
		return 0;

	
	pPetSystem->Update(0);
	// 0.25ГКё¶ґЩ °»ЅЕ.
	return PASSES_PER_SEC(1) / 4;
}

/// NOTE: 1ДіёЇЕН°Ў ёо°іАЗ ЖкА» °ЎБъ јц АЦґВБц Б¦ЗС... ДіёЇЕНё¶ґЩ °іјцё¦ ґЩёЈ°Ф ЗТ°Е¶уёй єЇјц·О іЦµо°Ў... АЅ..
/// °ЎБъ јц АЦґВ °іјцїН µїЅГїЎ јТИЇЗТ јц АЦґВ °іјц°Ў ЖІё± јц АЦґВµҐ АМ·±°З ±вИ№ ѕшАёґП АПґЬ №«ЅГ
const float PET_COUNT_LIMIT = 3;

///////////////////////////////////////////////////////////////////////////////////////
//  CPetActor
///////////////////////////////////////////////////////////////////////////////////////

CPetActor::CPetActor(LPCHARACTER owner, DWORD vnum, DWORD options)
{
	m_dwVnum = vnum;
	m_dwVID = 0;
	m_dwOptions = options;
	m_dwLastActionTime = 0;

	m_pkChar = 0;
	m_pkOwner = owner;

	m_originalMoveSpeed = 0;
	
	m_dwSummonItemVID = 0;
	m_dwSummonItemVnum = 0;
}

CPetActor::~CPetActor()
{
	this->Unsummon();

	m_pkOwner = 0;
}

void CPetActor::SetName(const char* name)
{
	std::string petName = m_pkOwner->GetName();

	if (0 != m_pkOwner && 
		0 == name && 
		0 != m_pkOwner->GetName())
	{
		petName += "'s Pet";
	}
	else
		petName += name;

	if (true == IsSummoned())
		m_pkChar->SetName(petName);

	m_name = petName;
}

bool CPetActor::Mount()
{
	if (0 == m_pkOwner)
		return false;

	if (true == HasOption(EPetOption_Mountable))
		m_pkOwner->MountVnum(m_dwVnum);

	return m_pkOwner->GetMountVnum() == m_dwVnum;;
}

void CPetActor::Unmount()
{
	if (0 == m_pkOwner)
		return;

	if (m_pkOwner->IsHorseRiding())
		m_pkOwner->StopRiding();
}

void CPetActor::Unsummon()
{
	if (true == this->IsSummoned())
	{
		// №цЗБ »иБ¦
		this->ClearBuff();
		this->SetSummonItem(NULL);
		if (NULL != m_pkOwner)
			m_pkOwner->ComputePoints();

		if (NULL != m_pkChar)
			M2_DESTROY_CHARACTER(m_pkChar);

		m_pkChar = 0;
		m_dwVID = 0;
	}
}

DWORD CPetActor::Summon(const char* petName, LPITEM pSummonItem, bool bSpawnFar)
{
	long x = m_pkOwner->GetX();
	long y = m_pkOwner->GetY();
	long z = m_pkOwner->GetZ();

	if (true == bSpawnFar)
	{
		x += (number(0, 1) * 2 - 1) * number(2000, 2500);
		y += (number(0, 1) * 2 - 1) * number(2000, 2500);
	}
	else
	{
		x += number(-100, 100);
		y += number(-100, 100);
	}

	if (0 != m_pkChar)
	{
		m_pkChar->Show (m_pkOwner->GetMapIndex(), x, y);
		m_dwVID = m_pkChar->GetVID();

		return m_dwVID;
	}
	
	m_pkChar = CHARACTER_MANAGER::instance().SpawnMob(
				m_dwVnum, 
				m_pkOwner->GetMapIndex(), 
				x, y, z,
				false, (int)(m_pkOwner->GetRotation()+180), false);

	if (0 == m_pkChar)
	{
		sys_err("[CPetSystem::Summon] Failed to summon the pet. (vnum: %d)", m_dwVnum);
		return 0;
	}

	m_pkChar->SetPet();

//	m_pkOwner->DetailLog();
//	m_pkChar->DetailLog();

	//ЖкАЗ ±№°Ўё¦ БЦАОАЗ ±№°Ў·О јіБ¤ЗФ.
	m_pkChar->SetEmpire(m_pkOwner->GetEmpire());

	m_dwVID = m_pkChar->GetVID();

	this->SetName(petName);

	// SetSummonItem(pSummonItem)ё¦ єОёҐ ИДїЎ ComputePointsё¦ єОёЈёй №цЗБ АыїлµК.
	this->SetSummonItem(pSummonItem);
	m_pkOwner->ComputePoints();
	m_pkChar->Show(m_pkOwner->GetMapIndex(), x, y, z);

	return m_dwVID;
}

bool CPetActor::_UpdatAloneActionAI(float fMinDist, float fMaxDist)
{
	float fDist = number(fMinDist, fMaxDist);
	float r = (float)number (0, 359);
	float dest_x = GetOwner()->GetX() + fDist * cos(r);
	float dest_y = GetOwner()->GetY() + fDist * sin(r);

	//m_pkChar->SetRotation(number(0, 359));        // №жЗвАє ·ЈґэАё·О јіБ¤

	//GetDeltaByDegree(m_pkChar->GetRotation(), fDist, &fx, &fy);

	// ґАЅјЗС ёш°Ё јУјє ГјЕ©; ГЦБѕ А§ДЎїН БЯ°Ј А§ДЎ°Ў °ҐјцѕшґЩёй °ЎБц ѕКґВґЩ.
	//if (!(SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy) 
	//			&& SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx/2, m_pkChar->GetY() + (int) fy/2)))
	//	return true;

	m_pkChar->SetNowWalking(true);

	//if (m_pkChar->Goto(m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy))
	//	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	if (!m_pkChar->IsStateMove() && m_pkChar->Goto(dest_x, dest_y))
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);

	m_dwLastActionTime = get_dword_time();

	return true;
}

// char_state.cpp StateHorseЗФјц ±ЧіЙ C&P -_-;
bool CPetActor::_UpdateFollowAI()
{
	if (0 == m_pkChar->m_pkMobData)
	{
		//sys_err("[CPetActor::_UpdateFollowAI] m_pkChar->m_pkMobData is NULL");
		return false;
	}
	
	// NOTE: ДіёЇЕН(Жк)АЗ їш·Ў АМµї јУµµё¦ ѕЛѕЖѕЯ ЗПґВµҐ, ЗШґз °Є(m_pkChar->m_pkMobData->m_table.sMovingSpeed)А» БчБўАыАё·О Бў±ЩЗШј­ ѕЛѕЖіѕ јцµµ АЦБцёё
	// m_pkChar->m_pkMobData °ЄАМ invalidЗС °жїм°Ў АЪБЦ №Я»эЗФ. ЗцАз ЅГ°Ј°ь°и»у їшАОАє ґЩАЅїЎ ЖДѕЗЗП°н АПґЬАє m_pkChar->m_pkMobData °ЄА» ѕЖї№ »зїлЗПБц ѕКµµ·П ЗФ.
	// ї©±вј­ ёЕ№ш °Л»зЗПґВ АМАЇґВ ГЦГК ГК±вИ­ ЗТ ¶§ Б¤»у °ЄА» Б¦ґл·О ёшѕтѕоїАґВ °жїмµµ АЦАЅ.. -_-;; ¤Р¤Р¤Р¤Р¤Р¤Р¤Р¤Р¤Р
	if (0 == m_originalMoveSpeed)
	{
		const CMob* mobData = CMobManager::Instance().Get(m_dwVnum);

		if (0 != mobData)
			m_originalMoveSpeed = mobData->m_table.sMovingSpeed;
	}
	float	START_FOLLOW_DISTANCE = 300.0f;		// АМ °Её® АМ»у ¶іѕоБцёй ВСѕЖ°Ў±в ЅГАЫЗФ
	float	START_RUN_DISTANCE = 900.0f;		// АМ °Её® АМ»у ¶іѕоБцёй ¶Щѕој­ ВСѕЖ°Ё.

	float	RESPAWN_DISTANCE = 4500.f;			// АМ °Её® АМ»у ёЦѕоБцёй БЦАО ї·Аё·О јТИЇЗФ.
	int		APPROACH = 200;						// Бў±Щ °Её®

	bool bDoMoveAlone = true;					// ДіёЇЕНїН °Ў±оАМ АЦА» ¶§ ИҐАЪ ї©±вАъ±в їтБчАП°ЗБц ї©єО -_-;
	bool bRun = false;							// ¶ЩѕоѕЯ ЗПіЄ?

	DWORD currentTime = get_dword_time();

	long ownerX = m_pkOwner->GetX();		long ownerY = m_pkOwner->GetY();
	long charX = m_pkChar->GetX();			long charY = m_pkChar->GetY();

	float fDist = DISTANCE_APPROX(charX - ownerX, charY - ownerY);

	if (fDist >= RESPAWN_DISTANCE)
	{
		float fOwnerRot = m_pkOwner->GetRotation() * 3.141592f / 180.f;
		float fx = -APPROACH * cos(fOwnerRot);
		float fy = -APPROACH * sin(fOwnerRot);
		if (m_pkChar->Show(m_pkOwner->GetMapIndex(), ownerX + fx, ownerY + fy))
		{
			return true;
		}
	}
	
	
	if (fDist >= START_FOLLOW_DISTANCE)
	{
		if( fDist >= START_RUN_DISTANCE)
		{
			bRun = true;
		}

		m_pkChar->SetNowWalking(!bRun);		// NOTE: ЗФјц АМё§єё°н ёШГЯґВ°ЗБЩ ѕЛѕТґВµҐ SetNowWalking(false) ЗПёй ¶ЩґВ°ЕАУ.. -_-;
		
		Follow(APPROACH);

		m_pkChar->SetLastAttacked(currentTime);
		m_dwLastActionTime = currentTime;
	}
	//else
	//{
	//	if (fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) > 10.f || fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) < 350.f)
	//	{
	//		m_pkChar->Follow(m_pkOwner, APPROACH);
	//		m_pkChar->SetLastAttacked(currentTime);
	//		m_dwLastActionTime = currentTime;
	//	}
	//}
	// Follow БЯАМБцёё БЦАО°ъ АПБ¤ °Её® АМі»·О °Ў±оїцБіґЩёй ёШГг
	else 
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	//else if (currentTime - m_dwLastActionTime > number(5000, 12000))
	//{
	//	this->_UpdatAloneActionAI(START_FOLLOW_DISTANCE / 2, START_FOLLOW_DISTANCE);
	//}

	return true;
}

bool CPetActor::Update(DWORD deltaTime)
{
	bool bResult = true;

	// Жк БЦАОАМ БЧѕъ°ЕіЄ, јТИЇµИ ЖкАЗ »уЕВ°Ў АМ»уЗПґЩёй ЖкА» ѕшѕЪ. (NOTE: °ЎІы°ЎґЩ АМ·± Аъ·± АМАЇ·О јТИЇµИ ЖкАМ DEAD »уЕВїЎ єьБцґВ °жїм°Ў АЦАЅ-_-;)
	// ЖкА» јТИЇЗС ѕЖАМЕЫАМ ѕш°ЕіЄ, і»°Ў °ЎБш »уЕВ°Ў ѕЖґП¶уёй ЖкА» ѕшѕЪ.
	if (m_pkOwner->IsDead() || (IsSummoned() && m_pkChar->IsDead()) 
		|| NULL == ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())
		|| ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetOwner() != this->GetOwner()
		)
	{
		this->Unsummon();
		return true;
	}

	if (this->IsSummoned() && HasOption(EPetOption_Followable))
		bResult = bResult && this->_UpdateFollowAI();

	return bResult;
}

//NOTE : БЦАЗ!!! MinDistanceё¦ Е©°Ф АвАёёй ±Ч єЇА§ёёЕ­АЗ єЇИ­µїѕИАє followЗПБц ѕКґВґЩ,
bool CPetActor::Follow(float fMinDistance)
{
	// °Ў·БґВ А§ДЎё¦ №Щ¶уєБѕЯ ЗСґЩ.
	if( !m_pkOwner || !m_pkChar) 
		return false;

	float fOwnerX = m_pkOwner->GetX();
	float fOwnerY = m_pkOwner->GetY();

	float fPetX = m_pkChar->GetX();
	float fPetY = m_pkChar->GetY();

	float fDist = DISTANCE_SQRT(fOwnerX - fPetX, fOwnerY - fPetY);
	if (fDist <= fMinDistance)
		return false;

	m_pkChar->SetRotationToXY(fOwnerX, fOwnerY);

	float fx, fy;

	float fDistToGo = fDist - fMinDistance;
	GetDeltaByDegree(m_pkChar->GetRotation(), fDistToGo, &fx, &fy);
	
	if (!m_pkChar->Goto((int)(fPetX+fx+0.5f), (int)(fPetY+fy+0.5f)) )
		return false;

	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0, 0);

	return true;
}

void CPetActor::SetSummonItem (LPITEM pItem)
{
	if (NULL == pItem)
	{
		m_dwSummonItemVID = 0;
		m_dwSummonItemVnum = 0;
		return;
	}

	m_dwSummonItemVID = pItem->GetVID();
	m_dwSummonItemVnum = pItem->GetVnum();
}

void CPetActor::GiveBuff()
{
	// ЖДИІ Жк №цЗБґВ ґшАьїЎј­ёё №Я»эЗФ.
	if (34004 == m_dwVnum || 34009 == m_dwVnum)
	{
		if (NULL == m_pkOwner->GetDungeon())
		{
			return;
		}
	}
	LPITEM item = ITEM_MANAGER::instance().FindByVID(m_dwSummonItemVID);
	if (NULL != item)
		item->ModifyPoints(true);
	return ;
}

void CPetActor::ClearBuff()
{
	if (NULL == m_pkOwner)
		return ;
	TItemTable* item_proto = ITEM_MANAGER::instance().GetTable(m_dwSummonItemVnum);
	if (NULL == item_proto)
		return;
	for (int i = 0; i < ITEM_APPLY_MAX_NUM; i++)
	{
		if (item_proto->aApplies[i].bType == APPLY_NONE)
			continue;
		m_pkOwner->ApplyPoint(item_proto->aApplies[i].bType, -item_proto->aApplies[i].lValue);
	}

	return ;
}

///////////////////////////////////////////////////////////////////////////////////////
//  CPetSystem
///////////////////////////////////////////////////////////////////////////////////////

CPetSystem::CPetSystem(LPCHARACTER owner)
{
//	assert(0 != owner && "[CPetSystem::CPetSystem] Invalid owner");

	m_pkOwner = owner;
	m_dwUpdatePeriod = 400;

	m_dwLastUpdateTime = 0;
}

CPetSystem::~CPetSystem()
{
	Destroy();
}

void CPetSystem::Destroy()
{
	for (TPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			delete petActor;
		}
	}
	event_cancel(&m_pkPetSystemUpdateEvent);
	m_petActorMap.clear();
}

/// Жк ЅГЅєЕЫ ѕчµҐАМЖ®. µо·ПµИ ЖкµйАЗ AI Гіё® µоА» ЗФ.
bool CPetSystem::Update(DWORD deltaTime)
{
	bool bResult = true;

	DWORD currentTime = get_dword_time();

	// CHARACTER_MANAGERїЎј­ ДіёЇЕН·щ UpdateЗТ ¶§ ёЕ°ієЇјц·О БЦґВ (Pulse¶у°н µЗѕоАЦґВ)°ЄАМ АМАь ЗБ·№АУ°ъАЗ ЅГ°ЈВчАМАОБЩ ѕЛѕТґВµҐ
	// АьЗф ґЩёҐ °ЄАМ¶уј­-_-; ї©±вїЎ АФ·ВАё·О µйѕоїАґВ deltaTimeАє АЗ№М°Ў ѕшАЅ¤Р¤Р	
	
	if (m_dwUpdatePeriod > currentTime - m_dwLastUpdateTime)
		return true;
	
	std::vector <CPetActor*> v_garbageActor;

	for (TPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor && petActor->IsSummoned())
		{
			LPCHARACTER pPet = petActor->GetCharacter();
			
			if (NULL == CHARACTER_MANAGER::instance().Find(pPet->GetVID()))
			{
				v_garbageActor.push_back(petActor);
			}
			else
			{
				bResult = bResult && petActor->Update(deltaTime);
			}
		}
	}
	for (std::vector<CPetActor*>::iterator it = v_garbageActor.begin(); it != v_garbageActor.end(); it++)
		DeletePet(*it);

	m_dwLastUpdateTime = currentTime;

	return bResult;
}

/// °ьё® ёс·ПїЎј­ ЖкА» Бцїт
void CPetSystem::DeletePet(DWORD mobVnum)
{
	TPetActorMap::iterator iter = m_petActorMap.find(mobVnum);

	if (m_petActorMap.end() == iter)
	{
		sys_err("[CPetSystem::DeletePet] Can't find pet on my list (VNUM: %d)", mobVnum);
		return;
	}

	CPetActor* petActor = iter->second;

	if (0 == petActor)
		sys_err("[CPetSystem::DeletePet] Null Pointer (petActor)");
	else
		delete petActor;

	m_petActorMap.erase(iter);	
}

/// °ьё® ёс·ПїЎј­ ЖкА» Бцїт
void CPetSystem::DeletePet(CPetActor* petActor)
{
	for (TPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		if (iter->second == petActor)
		{
			delete petActor;
			m_petActorMap.erase(iter);

			return;
		}
	}

	sys_err("[CPetSystem::DeletePet] Can't find petActor(0x%x) on my list(size: %d) ", petActor, m_petActorMap.size());
}

void CPetSystem::Unsummon(DWORD vnum, bool bDeleteFromList)
{
	CPetActor* actor = this->GetByVnum(vnum);

	if (0 == actor)
	{
		sys_err("[CPetSystem::GetByVnum(%d)] Null Pointer (petActor)", vnum);
		return;
	}
	actor->Unsummon();

	if (true == bDeleteFromList)
		this->DeletePet(actor);

	bool bActive = false;
	for (TPetActorMap::iterator it = m_petActorMap.begin(); it != m_petActorMap.end(); it++)
	{
		bActive |= it->second->IsSummoned();
	}
	if (false == bActive)
	{
		event_cancel(&m_pkPetSystemUpdateEvent);
		m_pkPetSystemUpdateEvent = NULL;
	}
}


CPetActor* CPetSystem::Summon(DWORD mobVnum, LPITEM pSummonItem, const char* petName, bool bSpawnFar, DWORD options)
{
	CPetActor* petActor = this->GetByVnum(mobVnum);

	// µо·ПµИ ЖкАМ ѕЖґП¶уёй »х·О »эјє ИД °ьё® ёс·ПїЎ µо·ПЗФ.
	if (0 == petActor)
	{
		petActor = M2_NEW CPetActor(m_pkOwner, mobVnum, options);
		m_petActorMap.insert(std::make_pair(mobVnum, petActor));
	}

	DWORD petVID = petActor->Summon(petName, pSummonItem, bSpawnFar);

	if (NULL == m_pkPetSystemUpdateEvent)
	{
		petsystem_event_info* info = AllocEventInfo<petsystem_event_info>();

		info->pPetSystem = this;

		m_pkPetSystemUpdateEvent = event_create(petsystem_update_event, info, PASSES_PER_SEC(1) / 4);	// 0.25ГК	
	}

	return petActor;
}


CPetActor* CPetSystem::GetByVID(DWORD vid) const
{
	CPetActor* petActor = 0;

	bool bFound = false;

	for (TPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		petActor = iter->second;

		if (0 == petActor)
		{
			sys_err("[CPetSystem::GetByVID(%d)] Null Pointer (petActor)", vid);
			continue;
		}

		bFound = petActor->GetVID() == vid;

		if (true == bFound)
			break;
	}

	return bFound ? petActor : 0;
}

/// µо·П µИ Жк БЯїЎј­ БЦѕоБш ёч VNUMА» °ЎБш ѕЧЕНё¦ №ЭИЇЗПґВ ЗФјц.
CPetActor* CPetSystem::GetByVnum(DWORD vnum) const
{
	CPetActor* petActor = 0;

	TPetActorMap::const_iterator iter = m_petActorMap.find(vnum);

	if (m_petActorMap.end() != iter)
		petActor = iter->second;

	return petActor;
}

size_t CPetSystem::CountSummoned() const
{
	size_t count = 0;

	for (TPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			if (petActor->IsSummoned())
				++count;
		}
	}

	return count;
}

void CPetSystem::RefreshBuff()
{
	for (TPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			if (petActor->IsSummoned())
			{
				petActor->GiveBuff();
			}
		}
	}
}