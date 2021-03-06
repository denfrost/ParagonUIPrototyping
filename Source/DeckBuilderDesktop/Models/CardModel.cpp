
#include "DeckBuilderDesktop.h"
#include "CardModel.h"

UCardModel::UCardModel(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool operator == (const UCardModel& LHS, const UCardModel& RHS)
{
	return LHS.CardName.EqualTo(RHS.CardName)
		&& LHS.Cost == RHS.Cost
		&& LHS.Type.EqualTo(RHS.Type)
		&& LHS.Affinity.EqualTo(RHS.Affinity)
		&& LHS.Rarity.EqualTo(RHS.Rarity)
		&& LHS.AllStats == RHS.AllStats
		&& LHS.BaseStats == RHS.BaseStats
		&& LHS.MaxedStats == RHS.MaxedStats;
}

UCardModel* UCardModel::ConstructFromCardData(const FCardData& CardData, UDataTable* StatDataTable)
{
	auto CardModel = NewObject<UCardModel>(GetTransientPackage(), NAME_None);
	CardModel->CardName = FText::FromString(CardData.CardName);
	CardModel->Cost = CardData.Cost;
	CardModel->Type = FText::FromString(CardData.Type);
	CardModel->Affinity = FText::FromString(CardData.Affinity);
	CardModel->Rarity = FText::FromString(CardData.Rarity);
	CardModel->AllStats = UCardStatModel::ConstructModelsFromCardData(CardData, TEXT(""), StatDataTable);
	CardModel->BaseStats = CardModel->AllStats.FilterByPredicate([=](const UCardStatModel* CardStatModel) {
		return CardStatModel->BonusType.ToString().Equals(TEXT("Base"));
	});
	CardModel->MaxedStats = CardModel->AllStats.FilterByPredicate([=](const UCardStatModel* CardStatModel) {
		return CardStatModel->BonusType.ToString().Equals(TEXT("Maxed"));
	});
	CardModel->Count = 6; // Placeholder value
	return CardModel;
}


UCardStatModel* UCardModel::GetStatByName(const FString& StatName) const
{
	for (auto Stat : AllStats)
	{
		if (Stat->Type.ToString().Equals(StatName))
		{
			return Stat;
		}
	}
	return nullptr;
}
