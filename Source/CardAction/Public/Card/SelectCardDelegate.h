#pragma once
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Card/CardData.h"

// �J�[�h��I���������̃f���Q�[�g
DECLARE_DELEGATE_OneParam(FOnSelectCard, UCardData*);
// �J�[�h�I����Ԃ���������f���Q�[�g
DECLARE_DELEGATE_OneParam(FOnUnSelectCard, UCardData*);
