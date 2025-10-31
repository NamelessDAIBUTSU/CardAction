// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>
#include <Character/MyPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "Animation/UMGSequencePlayer.h"
#include <Card/Effect/CardEffectSummonWeapon.h>
#include <Weapon/Weapon_ThrowKnife.h>
#include <Card/CardUtil.h>

void UCardWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (CardButton)
    {
        CardButton->OnClicked.AddDynamic(this, &UCardWidget::OnCardClicked);
    }
}

void UCardWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (CardButton)
    {
        CardButton->IsFocusable = false;
    }
}

void UCardWidget::SetupCardData(UCardData* Data)
{
    CardData = Data;

    if (CardData == nullptr)
        return;

    if (GetGameInstance() == nullptr)
        return;

    UCardUtil* CardUtil = GetGameInstance()->GetSubsystem<UCardUtil>();
    if (CardUtil == nullptr)
        return;

    // 各ウィジェットの設定
    // 名前
    if (NameText)
    {
        NameText->SetText(FText::FromName(CardData->Name));
    }
    // ダメージ
    if (DamageText)
    {
        // エフェクトからデフォルトオブジェクトを取得してダメージを取得
        if (CardData->EffectClass)
        {
            UCardEffectSummonWeapon* Effect = CardData->EffectClass->GetDefaultObject<UCardEffectSummonWeapon>();
            if (Effect && Effect->WeaponClass)
            {
                AWeaponActorBase* WeaponActor = Effect->WeaponClass->GetDefaultObject<AWeaponActorBase>();
                if (WeaponActor)
                {
                    FFormatNamedArguments Args;
                    Args.Add(TEXT("Damage"), WeaponActor->Damage);
                    DamageText->SetText(FText::Format(FTextFormat::FromString("{Damage}"), Args));
                }
            }
            
        }
    }
    // カードベース
    if (CardBase)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(CardUtil->GetCardBaseTexture(CardData->Rarity));
        CardBase->SetBrush(Brush);
    }
    // テクスチャ
    if (CardImage)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(CardData->CardTexture);
        CardImage->SetBrush(Brush);
    }
    // カードタイプのアイコン設定
    if (CardTypeIcon)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(CardUtil->GetCardTypeIconTexture(CardData->CardType));
        CardTypeIcon->SetBrush(Brush);
    }
    // 属性タイプのアイコン設定
    if (ElementTypeIcon)
    {
        // エフェクトからデフォルトオブジェクトを取得してダメージを取得
        if (CardData->EffectClass)
        {
            UCardEffectSummonWeapon* Effect = CardData->EffectClass->GetDefaultObject<UCardEffectSummonWeapon>();
            if (Effect && Effect->WeaponClass)
            {
                AWeaponActorBase* WeaponActor = Effect->WeaponClass->GetDefaultObject<AWeaponActorBase>();
                if (WeaponActor)
                {
                    FSlateBrush Brush;
                    Brush.SetResourceObject(CardUtil->GetElementTypeIconTexture(WeaponActor->ElementType));
                    ElementTypeIcon->SetBrush(Brush);
                }
            }
        }
    }
}

void UCardWidget::Initialize(UCardData* Data, const FCardWidgetOption& WidgetOption)
{
    // ウィジェットの初期化
    SetupCardData(Data);

    // 表示オプションの設定
    Option = WidgetOption;
}

// クリック時
void UCardWidget::OnCardClicked()
{
    if (Option.bCanMouseOver == false)
        return;

    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController == nullptr)
        return;
    if (PlayerController->MainHUDWidget == nullptr)
        return;
    UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
    if (CardSelectWidget == nullptr)
        return;

    // 選択
    if (bSelected == false)
    {
        // 手札がマックスの場合、選択できないようにする
        if (CardSelectWidget->IsSelectMax())
            return;

        if (Option.SelectCardDelegate.IsBound())
        {
            Option.SelectCardDelegate.Execute(CardData);

            // 選択中にする
            bSelected = true;

            // 選択中用のホバー画像を表示
            if (SelectAnim)
            {
                PlayAnimation(SelectAnim);
            }

            // 選択番号テキストの更新
            SetupSelectNum();
        }
    }
    // 選択解除
    else
    {
        if (Option.UnSelectCardDelegate.IsBound())
        {
            Option.UnSelectCardDelegate.Execute(CardData);

            // 未選択にする
            bSelected = false;

            if (UnSelectAnim)
            {
                // 選択中用のホバー画像を非表示
                UUMGSequencePlayer* SequencePlayer = PlayAnimation(UnSelectAnim);
                // アニメーション終了後、ほかの選択中のカードの選択番号を更新する
                if (SequencePlayer)
                {
                    SequencePlayer->OnSequenceFinishedPlaying().AddUObject(CardSelectWidget, &UCardSelectWidget::OnRefleshSelectNumText);
                }
            }
        }
    }
}

// マウスオーバー時
void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (Option.bCanMouseOver == false)
        return;

    // スケール変更
    if (Option.bChangeScale && MouseOverAnim)
    {
        StopAnimation(MouseReleaseAnim);
        PlayAnimation(MouseOverAnim);
    }

    // ツールチップ表示
    if (Option.bShowToolTip)
    {

    }
}

// マウスオーバーから離れた時
void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    if (Option.bCanMouseOver == false)
        return;

    // スケール変更
    if (Option.bChangeScale && MouseReleaseAnim)
    {
        StopAnimation(MouseOverAnim);
        PlayAnimation(MouseReleaseAnim);
    }

    // ツールチップ非表示
    if (Option.bShowToolTip)
    {

    }
}

// 効果発動
void UCardWidget::ExecuteEffect()
{
    if (IsValid(this) == false)
    {
        UE_LOG(LogTemp, Error, TEXT("this is not valid"));
        return;
    }

    // データ無しなら発動無効
    if (CardData == nullptr)
        return;

    // すでに発動中は発動無効
    if (IsAnimationPlaying(UseCardAnim))
        return;

    // 効果発動
    if (CardData->EffectClass)
    {
        if (UCardEffectBase* Effect = NewObject<UCardEffectBase>(this, CardData->EffectClass))
        {
            Effect->ExecuteEffect();
        }
    }

    // アニメーション
    if (UseCardAnim)
    {
        UUMGSequencePlayer* SequencePlayer = PlayAnimation(UseCardAnim);

        // アニメーション終了後
        if (SequencePlayer)
        {
            SequencePlayer->OnSequenceFinishedPlaying().AddLambda([this, &SequencePlayer](UUMGSequencePlayer& SeqPlayer)
                {
                    if (IsValid(this) == false)
                        return;

                    // カードデータをリセット
                    SetupCardData(nullptr);
                });
        }
    }
}

// 選択番号テキストの設定
void UCardWidget::SetupSelectNum()
{
    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController == nullptr)
        return;
    if (PlayerController->MainHUDWidget == nullptr)
        return;
    UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
    if (CardSelectWidget == nullptr)
        return;

    // 選択番号更新
    if (SelectNum && CardData)
    {
        int Index = CardSelectWidget->GetSelectIndex(CardData->UniqueID);

        FFormatNamedArguments Args;
        Args.Add(TEXT("Num"), Index + 1);
        SelectNum->SetText(FText::Format(FTextFormat::FromString("{Num}"), Args));
    }
}

// デフォルトアニメーションに戻す
void UCardWidget::PlayDefaultAnimation()
{
    if (DefaultAnim)
    {
        PlayAnimation(DefaultAnim);
    }
}
