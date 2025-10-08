// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SelectedCardsWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBoxSlot.h"

void USelectedCardsWidget::AddToSelectedCards(UCardData* Data)
{
	if (GetWorld() == nullptr || CardsWidgetClass == nullptr || Data == nullptr)
		return;

	UCardWidget* NewSelectedCard = CreateWidget<UCardWidget>(GetWorld(), CardsWidgetClass);
	if (NewSelectedCard)
	{
		NewSelectedCard->InitializeWidget(Data);

		if (CardsHorizontalBox)
		{
			UHorizontalBoxSlot* BoxSlot = Cast<UHorizontalBoxSlot>(CardsHorizontalBox->AddChildToHorizontalBox(NewSelectedCard));
			if (BoxSlot)
			{
				BoxSlot->SetPadding(EdgeMargin);
			}
		}
	}
}

void USelectedCardsWidget::RemoveFromSelectedCards(UCardData* Data)
{
	if (CardsHorizontalBox)
	{
		TArray<UWidget*> Children = CardsHorizontalBox->GetAllChildren();
		auto* Found = Children.FindByPredicate([Data](UWidget* Obj)
			{
				UCardWidget* CardWidget = Cast<UCardWidget>(Obj);
				if (CardWidget == nullptr)
					return false;

				return CardWidget->GetCardData()->Name == Data->Name;
			});

		if (Found)
		{
			CardsHorizontalBox->RemoveChild(*Found);
		}
	}
}

// î≠ìÆ
void USelectedCardsWidget::OnExecute()
{
	// èáî‘Ç…ÉJÅ[Éhå¯â î≠ìÆ
	TArray<UWidget*> Children = CardsHorizontalBox->GetAllChildren();
	for (UWidget* Child : Children)
	{
		UCardWidget* Card = Cast<UCardWidget>(Child);
		if (Card)
		{
			Card->ExecuteEffect();
		}
	}
}
