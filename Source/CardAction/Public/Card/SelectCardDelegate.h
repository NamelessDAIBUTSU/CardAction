#pragma once
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Card/CardData.h"

// カードを選択した時のデリゲート
DECLARE_DELEGATE_OneParam(FOnSelectCard, UCardData*);
// カード選択状態を解除するデリゲート
DECLARE_DELEGATE_OneParam(FOnUnSelectCard, UCardData*);
