// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "FriendsAndChatPrivatePCH.h"
#include "ClanInfoViewModel.h"
#include "ClanInfo.h"
#include "ClanMemberList.h"
#include "FriendListViewModel.h"

class FClanInfoViewModelImpl
	: public FClanInfoViewModel
{
public:

	virtual FText GetClanTitle() override
	{
		return ClanInfo->GetTitle();
	}

	virtual int32 GetMemberCount() override
	{
		return ClanInfo->GetMemberList().Num();
	}

	virtual TSharedRef< FFriendListViewModel > GetFriendListViewModel() override
	{
		return FFriendListViewModelFactory::Create(FClanMemberListFactory::Create(ClanInfo, FriendsAndChatManager.Pin().ToSharedRef()), EFriendsDisplayLists::ClanMemberDisplay);
	}

	virtual FText GetListCountText() const override
	{
		return FText::AsNumber(ClanInfo->GetMemberList().Num());
	}

	virtual FText GetClanBrushName() const override
	{
		return ClanInfo->GetClanBrushName();
	}

private:
	void Initialize()
	{

	}

private:
	FClanInfoViewModelImpl(const TSharedRef<IClanInfo>& ClanInfo, const TSharedRef<FFriendsAndChatManager>& FriendsAndChatManager)
		: ClanInfo(ClanInfo)
		, FriendsAndChatManager(FriendsAndChatManager)
	{
	}

	TSharedRef<IClanInfo> ClanInfo;
	TWeakPtr<FFriendsAndChatManager> FriendsAndChatManager;
	friend FClanInfoViewModelFactory;
};

TSharedRef< FClanInfoViewModel > FClanInfoViewModelFactory::Create(
	const TSharedRef<IClanInfo>& ClanInfo,
	const TSharedRef<FFriendsAndChatManager>& FriendsAndChatManager
	)
{
	TSharedRef< FClanInfoViewModelImpl > ViewModel(new FClanInfoViewModelImpl(ClanInfo, FriendsAndChatManager));
	ViewModel->Initialize();
	return ViewModel;
}