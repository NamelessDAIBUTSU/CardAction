// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardDetailPanelWidget.h"
#include <Card/CardData.h>
#include <Card/Effect/CardEffectSummonWeapon.h>
#include <Card/CardUtil.h>

void UCardDetailPanelWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCardDetailPanelWidget::Setup(UCardData* Data)
{
	if (Data == nullptr)
		return;
    
    // カード名テキスト
    if (CardNameText)
    {
        CardNameText->SetText(FText::FromName(Data->Name));
    }

    // レアリティテキスト
    if (RarityText)
    {
        FString RarityString = UCardUtil::CardEnumToString(Data->Rarity);
        RarityText->SetText(FText::FromString(RarityString));

        // レアリティに対応するカラー対応
        RarityText->SetColorAndOpacity(UCardUtil::GetRarityColor(Data->Rarity));
    }

    // 効果からダメージと属性を取得
    if (Data->EffectClass)
    {
        UCardEffectSummonWeapon* Effect = Data->EffectClass->GetDefaultObject<UCardEffectSummonWeapon>();
        if (Effect && Effect->WeaponClass)
        {
            if (AWeaponActorBase* WeaponActor = Effect->WeaponClass->GetDefaultObject<AWeaponActorBase>())
            {
                // 属性テキスト
                if (ElementText)
                {
                    FString ElementString = UCardUtil::CardEnumToString(WeaponActor->ElementType);
                    ElementText->SetText(FText::FromString(ElementString));
                    
                    // 属性に対応するカラー対応
                    ElementText->SetColorAndOpacity(UCardUtil::GetElementColor(WeaponActor->ElementType));
                }

                // ダメージテキスト
                if (DamageText)
                {
                    FFormatNamedArguments Args;
                    Args.Add(TEXT("Damage"), WeaponActor->Damage);
                    DamageText->SetText(FText::Format(FTextFormat::FromString("{Damage}"), Args));
                }
            }
        }
    }

    // 効果テキスト
    if (CardDescText)
    {
        // 改行を入れる
        FString OriginDescText = Data->Description;
        FString DescText = OriginDescText.Replace(TEXT("\\n"), TEXT("\n"));

        CardDescText->SetText(FText::FromString(DescText));
    }
}
