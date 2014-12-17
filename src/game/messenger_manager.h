#ifndef __INC_MESSENGER_MANAGER_H
#define __INC_MESSENGER_MANAGER_H

#include "db.h"

typedef std::string keyT;
typedef const std::string& keyA;

typedef std::set<std::string> KeyTSet;
typedef std::map<std::string, KeyTSet> KeyTRelation;

class MessengerManager : public singleton<MessengerManager>
{
	public:
		MessengerManager();
		virtual ~MessengerManager();

	public:
		void	P2PLogin(const std::string& account);
		void	P2PLogout(const std::string& account);

		void	Login(const std::string& account);
		void	Logout(const std::string& account);

		void	RequestToAdd(LPCHARACTER ch, LPCHARACTER target);
		void	AuthToAdd(const std::string& account, const std::string& companion, bool bDeny);

		void	__AddToList(const std::string& account, const std::string& companion);	// 실제 m_Relation, m_InverseRelation 수정하는 메소드
		void	AddToList(const std::string& account, const std::string& companion);

		void	__RemoveFromList(const std::string& account, const std::string& companion); // 실제 m_Relation, m_InverseRelation 수정하는 메소드
		void	RemoveFromList(const std::string& account, const std::string& companion);

		void	RemoveAllList(const std::string& account);

		void	Initialize();

	private:
		void	SendList(const std::string& account);
		void	SendLogin(const std::string& account, const std::string& companion);
		void	SendLogout(const std::string& account, const std::string& companion);

		void	LoadList(SQLMsg * pmsg);

		void	Destroy();

		KeyTSet			m_set_loginAccount;
		KeyTRelation	m_Relation;
		KeyTRelation	m_InverseRelation;
		std::set<DWORD>			m_set_requestToAdd;
};

#endif
