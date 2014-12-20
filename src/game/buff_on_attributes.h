#ifndef __METIN2_BUFF_ON_ATTRIBUTES_H
#define __METIN2_BUFF_ON_ATTRIBUTES_H

class CHARACTER;

class CBuffOnAttributes
{
public:
	CBuffOnAttributes(LPCHARACTER pOwner, BYTE m_point_type, std::vector <BYTE>* vec_buff_targets);
	~CBuffOnAttributes();

	// АеВш БЯ АМёйј­, m_p_vec_buff_wear_targetsїЎ ЗШґзЗПґВ ѕЖАМЕЫАО °жїм, ЗШґз ѕЖАМЕЫАё·О АОЗШ єЩАє Иї°ъё¦ Б¦°Е.
	void RemoveBuffFromItem(LPITEM pItem);
	// m_p_vec_buff_wear_targetsїЎ ЗШґзЗПґВ ѕЖАМЕЫАО °жїм, ЗШґз ѕЖАМЕЫАЗ attributeїЎ ґлЗС Иї°ъ ГЯ°Ў.
	void AddBuffFromItem(LPITEM pItem);
	// m_bBuffValueё¦ №ЩІЩ°н, №цЗБАЗ °Єµµ №ЩІЮ.
	void ChangeBuffValue(BYTE bNewValue);
	// CHRACTRE::ComputePointsїЎј­ јУјєДЎё¦ ГК±вИ­ЗП°н ґЩЅГ °и»кЗП№З·О, 
	// №цЗБ јУјєДЎµйА» °­Б¦АыАё·О ownerїЎ°Ф БЬ.
	void GiveAllAttributes();

	// m_p_vec_buff_wear_targetsїЎ ЗШґзЗПґВ ёрµз ѕЖАМЕЫАЗ attributeё¦ typeє°·О ЗХ»кЗП°н,
	// ±Ч attributeµйАЗ (m_bBuffValue)% ёёЕ­А» №цЗБ·О БЬ.
	bool On(BYTE bValue);
	// №цЗБ Б¦°Е ИД, ГК±вИ­
	void Off();

	void Initialize();
private:
	LPCHARACTER m_pBuffOwner;
	BYTE m_bPointType;
	BYTE m_bBuffValue;
	std::vector <BYTE>* m_p_vec_buff_wear_targets;
	
	// apply_type, apply_value ЖдѕоАЗ ёК
	typedef std::map <BYTE, int> TMapAttr;
	// m_p_vec_buff_wear_targetsїЎ ЗШґзЗПґВ ёрµз ѕЖАМЕЫАЗ attributeё¦ typeє°·О ЗХ»кЗПї© °ЎБц°н АЦАЅ.
	TMapAttr m_map_additional_attrs;

};

#endif
