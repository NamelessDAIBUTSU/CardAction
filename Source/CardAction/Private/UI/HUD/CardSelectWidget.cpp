// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSelectWidget.h"
#include "Animation/WidgetAnimationEvents.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>
#include <Kismet/GameplayStatics.h>
#include <Character/MyPlayerController.h>
#include <UI/HUD/CardDetailPanelWidget.h>

void UCardSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // カード詳細ウィジェットを生成
    CreateCardDetailWidget();
}

// 初期化
bool UCardSelectWidget::Initialize()
{
    if (Super::Initialize() == false)
        return false;

    // 決定時のコールバック登録
    if (DecideSelectButton)
    {
        DecideSelectButton->OnClicked.AddDynamic(this, &UCardSelectWidget::OnDecide);
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

        // 手札に加える
        for (int i = 0; i < SelectCards.Num(); ++i)
        {
            HandCardsWidget->AddToHandCards(i, SelectCards[i]);

            // 加えたカードのウィジェットの状態をデフォルトに戻す
            HandCardsWidget->PlayDefaultAnimation(i);
        }

        // 空があればnullptrを設定
        for (int i = SelectCards.Num(); i < MAX_HAND_CARDS_NUM; ++i)
        {
            HandCardsWidget->AddToHandCards(i, nullptr);
        }
    }
}

void UCardSelectWidget::PlayInAnim()
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

                    SelectCards.RemoveSingle(CardData);
                });

            CardWidget->Initialize(CardDataArray[i], Option);

            CardWidget->SetRenderScale(FVector2D(1.2f));
        }

        // サイズボックスに追加
        CardBoxArray[i]->RemoveChildAt(0);
        if (USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBoxArray[i]->AddChild(CardWidget)))
        {
        }
    }
}

// 最大まで選択しているか
bool UCardSelectWidget::IsSelectMax() const 
{
    return SelectCards.Num() == MAX_HAND_CARDS_NUM; 
}

// 該当カードの順番取得
int UCardSelectWidget::GetSelectIndex(const FName& ID)
{
    for (int index = 0; index < SelectCards.Num(); ++index)
    {
        if (SelectCards[index]->UniqueID == ID)
            return index;
    }

    return -1;
}

// 選択中カードの選択番号テキストをリフレッシュする
void UCardSelectWidget::OnRefleshSelectNumText(UUMGSequencePlayer& Player)
{
    for (auto* CardBox : CardBoxArray)
    {
        if (CardBox == nullptr)
            continue;

        if (UCardWidget* CardWidget = Cast<UCardWidget>(CardBox->GetChildAt(0)))
        {
            CardWidget->SetupSelectNum();
        }
    }
}

// カード詳細ウィジェットの生成
void UCardSelectWidget::CreateCardDetailWidget()
{
    if (CardDetailPanelWidgetClass == nullptr || CardDetailPanelBox == nullptr)
        return;

    CardDetailPanelWidget = CreateWidget<UCardDetailPanelWidget>(GetWorld(), CardDetailPanelWidgetClass);
    if (CardDetailPanelWidget == nullptr)
        return;

    // サイズボックスに追加
    if (USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardDetailPanelBox->AddChild(CardDetailPanelWidget)))
    {
    }
}
