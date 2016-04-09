#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "Filters/CardFilter.h"
#include "Filters/CardFilterOr.h"
#include "Filters/CardFilterAnd.h"
#include "Filters/CardFilterByStatContains.h"
#include "CardModel.h"
#include "CardListModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardListModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<UCardModel*> AllCards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card List")
	UCardFilter* Filter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<bool> FilterStates;

	static UCardListModel* ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable);

	UFUNCTION(BlueprintCallable, Category = "Card List")
	virtual void FilterCards();


	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* SetAffinityFilters(TArray<FString> AffinityNames);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterByText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterByBaseStat(const FString& StatName);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterByCost(int32 CostValue);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterBySlot(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveAllFilters();

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveFilter(UCardFilter* FilterToRemove);

protected:

	UPROPERTY()
	UCardFilterAnd* MainFilter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	UCardFilterAnd* UserFilter;

	UPROPERTY()
	UCardFilterOr* AffinityFilter;

	UPROPERTY()
		UCardFilterByStatContains* TextFilter;

	UPROPERTY()
		UCardFilter* SlotFilter;

	UPROPERTY()
	TArray<UCardFilter*> ActiveFilters;

	void ConstructDefaultFilters();

};