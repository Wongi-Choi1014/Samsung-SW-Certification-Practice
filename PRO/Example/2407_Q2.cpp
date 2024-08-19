//Script 형태 실행을 위해 User / Main 파일 Merge
//57초과 시 숫자가 아님
//user.cpp

#define MAX_N			(5)
#define MAX_L			(8)
#include <iostream>
#include <set>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;


struct Result
{
	int size;
	char mNameList[MAX_N][MAX_L + 1];
	char mTelephoneList[MAX_N][MAX_L + 1];
};

struct Contact
{
	char mNameList[MAX_L + 1];
	char mTelephoneList[MAX_L + 1];
/*
	bool operator=(const Contact& Right)const{
		return strcmp(mNameList, Right.mNameList) || strcmp(mTelephoneList, Right.mTelephoneList);
	}
	*/
	bool operator==(const Contact& Right)const{
		return (strcmp(mNameList, Right.mNameList)==0||strcmp(mTelephoneList, Right.mTelephoneList)==0);
	}
	bool operator<(const Contact& Right)const{
		//if(strcmp(mNameList, Right.mNameList)<0)
        //if(strcmp(mNameList, Right.mNameList)==0)
		//	return false;
		//if(strcmp(mNameList, Right.mNameList)<0 || strcmp(mTelephoneList, Right.mTelephoneList)<0)
        if(strcmp(mNameList, Right.mNameList)<0)
			return true;
		return false;
	}
};
set<Contact> Contact_DB;
vector<Contact> Log_DB;

void init()
{
	Contact_DB.clear();
	Log_DB.clear();
	return;
}

void add(char mName[], char mTelephone[])
{
	//*중복, Log 제거 필요
	//Contact New_Contact{*mName+'\0', *mTelephone+'\0'};
	Contact New_Contact;
    strcpy(New_Contact.mNameList,mName);
    strcpy(New_Contact.mTelephoneList,mTelephone);
	Contact_DB.insert(New_Contact);
	
	//이전에 Contact 전달 안되었으며 Call 호출 안되었으므로 Log는 없는상태임 
	//auto is_log = find(Log_DB.begin(),Log_DB.end(),New_Contact);
	//if(is_log!= Log_DB.end());
	//	Log_DB.erase(is_log);
	Log_DB.push_back(New_Contact);
	//cout <<"Input : " << mStr << "Output : "<<ret.mTelephoneList[i]<<endl;
	return;
}

void remove(char mStr[])
{
	//Name
	//if(int(mStr[0])>57)
	//Telephone
	//Contact New_Contact{*mStr+'\0', *mStr+'\0'};
	Contact New_Contact;
    strcpy(New_Contact.mNameList,mStr);
    strcpy(New_Contact.mTelephoneList,mStr);

    auto is_log = find(Log_DB.begin(),Log_DB.end(),New_Contact);

    if(is_log!= Log_DB.end())
    {
        strcpy(New_Contact.mNameList, is_log->mNameList);
        Log_DB.erase(is_log);
    }

	//Contact DB에 존재 시 DB 삭제
	auto is_contact = Contact_DB.find(New_Contact);
	if(is_contact!=Contact_DB.end())
		Contact_DB.erase(is_contact);
        
	return;
}

void call(char mTelephone[])
{
	Contact New_Contact;
    strcpy(New_Contact.mNameList,mTelephone);
    strcpy(New_Contact.mTelephoneList,mTelephone);
	
	auto is_log = find(Log_DB.begin(),Log_DB.end(),New_Contact);
	if(is_log!= Log_DB.end())
    {
        strcpy(New_Contact.mNameList, is_log->mNameList);
        Log_DB.erase(is_log);
    }
	Log_DB.push_back(New_Contact);
	return;
}

Result search(char mStr[])
{
	Result ret;
	ret.size = 0;
	//Contact New_Contact{*mStr+'\0', *mStr+'\0'};
	for(auto it = Log_DB.rbegin();it!=Log_DB.rend();it++)
	{
		if(ret.size>=5)
			break;
		//for(int i=0;i<sizeof(*mStr)/sizeof(char);i++)
        bool is_find= false;
        if(int(mStr[0])>57)
        {
            if(strncmp(mStr,it->mNameList,strlen(mStr))==0)
                is_find=true;
        }
        else
        {
            if(strncmp(mStr,it->mTelephoneList,strlen(mStr))==0)
                is_find=true;
        }
        //if(*it==New_Contact)
        if(is_find==true)
        {
            strcpy(ret.mNameList[ret.size], it->mNameList);
            strcpy(ret.mTelephoneList[ret.size], it->mTelephoneList);
            ret.size++;
        }
	}

	return ret;
}


//main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define CMD_INIT		(100)
#define CMD_ADD			(200)
#define CMD_REMOVE		(300)
#define CMD_CALL		(400)
#define CMD_SEARCH		(500)

#define MAX_N			(5)
#define MAX_L			(8)
/*
struct Result
{
	int size;
	char mNameList[MAX_N][MAX_L + 1];
	char mTelephoneList[MAX_N][MAX_L + 1];
};
*/
extern void init();
extern void add(char mName[], char mTelephone[]);
extern void remove(char mStr[]);
extern void call(char mTelephone[]);
extern Result search(char mStr[]);

static bool run()
{
	int Q;
	char mName[MAX_L + 1];
	char mTelephone[MAX_L + 1];
	char mStr[MAX_L + 1];

	Result ret;

	int ans;

	scanf("%d", &Q);

	bool okay = false;

	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		scanf("%d", &cmd);
		switch(cmd)
		{
		case CMD_INIT:
			init();
			okay = true;
			break;
		case CMD_ADD:
			scanf("%s %s", mName, mTelephone);
			add(mName, mTelephone);
			break;
		case CMD_REMOVE:
			scanf("%s", mStr);
			remove(mStr);
			break;
		case CMD_CALL:
			scanf("%s", mTelephone);
			call(mTelephone);
			break;
		case CMD_SEARCH:
			scanf("%s", mStr);
			ret = search(mStr);
			scanf("%d", &ans);
			if (ret.size != ans)
				okay = false;
			for (int i = 0; i < ans; ++i)
			{
				scanf("%s", mStr);
				if (mStr[0] != '$' && strcmp(mStr, ret.mNameList[i]) != 0)
					okay = false;
				scanf("%s", mStr);
				if (strcmp(mStr, ret.mTelephoneList[i]) != 0)
					okay = false;
                cout<< "Answer : "<<mStr<<" My : "<<ret.mTelephoneList[i]<<'\n';
			}
			break;
		default:
			okay = false;
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int TC, MARK;

	scanf("%d %d", &TC, &MARK);
	for (int tc = 1; tc <= TC; ++tc)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}