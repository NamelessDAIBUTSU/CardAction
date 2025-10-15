// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSelectWidget.h"
#include "Animation/WidgetAnimationEvents.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>
#include <Kismet/GameplayStatics.h>
#include <Character/MyPlayerController.h>

// 初期化
bool UCardSelectWidget::Initialize()
{
    if (Super::Initialize() == false)
        return false;

    // 決定時のコールバック登録
    if (DecideButton)
    {
        DecideButton->OnClicked.AddDynamic(this, &UCardSelectWidget::OnDecide);
    }

    // Hidden→Visibleに変わったときにフラグを初期化する
    OnVisibilityChanged.AddDynamic(this, &UCardSelectWidget::OnChangeVisibility);

    // カードボックスウィジェットを配列にいれる
    CardBoxArray.Add(CardBox0);
    CardBoxArray.Add(CardBox1);
    CardBoxArray.Add(CardBox2);
    CardBoxArray.Add(CardBox3);
    CardBoxArray.Add(CardBox4);
    CardBoxArray.Add(CardBox5);
    CardBoxArray.Add(CardBox6);
    CardBoxArray.Add(CardBox7);

    return true;
}

void UCardSelectWidget::OnDecide()
{
    if (OutAnim)
    {
        bIsPlayingOutAnim = true;

        // バインド解除
        UnbindAllFromAnimationFinished(OutAnim);

        // Outアニメーションを再生
        StopAnimation(OutAnim); 
        PlayAnimation(OutAnim);

        // アニメーション終了時に確定フラグを立てるようコールバック登録
        FWidgetAnimationDynamicEvent Delegate;
        Delegate.BindUFunction(this, FName("OnChangeIsDecided"));
        BindToAnimationFinished(OutAnim, Delegate);

        UE_LOG(LogTemp, Warning, TEXT("OnDecide"));
    }
}

// ビジブル変更時のコールバック
void UCardSelectWidget::OnChangeVisibility(ESlateVisibility NextVisibility)
{
    if (NextVisibility == ESlateVisibility::Visible)
    {
        bIsDecided = false;

        // 選択中カードの配列を初期化
        for (int i = SelectCards.Num() - 1; i >= 0; --i)
        {
            SelectCards.RemoveAt(i);
        }

        // 手札カードを初期化
        AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        if (PlayerController == nullptr)
            return;
        if (PlayerController->MainHUDWidget == nullptr)
            return;
        UHandCardsWidget* HandCardsWidget = PlayerController->MainHUDWidget->HandCardsWidget;
        if (HandCardsWidget == nullptr)
            return;
        HandCardsWidget->ResetHandCards();
    }
}

void UCardSelectWidget::OnChangeIsDecided()
{
    if (bIsPlayingOutAnim == false)
        return;

    bIsDecided = true;
    bIsPlayingOutAnim = false;

    // 選択中のカードを手札に加える
    {
        AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        if (PlayerController == nullptr)
            return;
        if (PlayerController->MainHUDWidget == nullptr)
            return;
        UHandCardsWidget* HandCardsWidget = PlayerController->MainHUDWidget->HandCardsWidget;
        if (HandCardsWidget == nullptr)
            return;

        for (int i = 0; i < SelectCards.Num(); ++i)
        {
            HandCardsWidget->AddToHandCards(i, SelectCards[i]);
        }

        // 空があればnullptrを設定
        for (int i = SelectCards.Num(); i < MAX_HAND_CARDS_NUM; ++i)
        {
            HandCardsWidget->AddToHandCards(i, nullptr);
        }
    }
}

void UCardSelectWidget::PlayInAnimation()
{
    if (InAnim)
    {
        StopAnimation(InAnim);
        PlayAnimation(InAnim);
    }
}

// カードウィジェットの生成
void UCardSelectWidget::CreateCardWidgets(const TArray<UCardData*>& CardDataArray)
{
    if (CardWidgetClass == nullptr)
        return;

    for (int i = 0; i < CardDataArray.Num(); ++i)
    {
        // ずれない想定だけど、カードボックスが存在しなかったら抜ける
        if (CardBoxArray.Num() <= i || CardBoxArray[i] == nullptr)
            break;

        // カードウィジェットの生成
        UCardWidget* CardWidget = CreateWidget<UCardWidget>(GetWorld(), CardWidgetClass);
        if (CardWidget == nullptr)
            return;

        // カードデータを初期化
        {
            FCardWidgetOption Option;
            Option.bChangeScale = false;

            // デリゲートに選択カード配列の更新の処理を入れる
            Option.SelectCardDelegate.BindLambda([this](UCardData* CardData)
                {
                    if (IsValid(this) == false)
                        return;
                    if (SelectCards.Num() >= MAX_HAND_CARDS_NUM)
                        return;
                    if (CardData == nullptr)
                        return;

                    SelectCards.Add(CardData);
                });
            Option.UnSelectCardDelegate.BindLambda([this](UCardData* CardData)
                {
                    if (IsValid(this) == false)
                        return;
                    if (CardData == nullptr)
                        return;

                    SelectCards.Remove(CardData);
                });

            CardWidget->Initialize(CardDataArray[i], Option);
        }

        // サイズボックスに追加
        CardBoxArray[i]->RemoveChildAt(0);
        if (USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBoxArray[i]->AddChild(CardWidget)))
        {
        }
    }
}
