// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMyActorTestClassTest.h"

#include "Misc/AutomationTest.h"
#include "MyActorTestClass.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTestActorTests, "Project.MyTestActorTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMyTestActorTests::RunTest(const FString& Parameters)
{
    AMyActorTestClass* TestActor = NewObject<AMyActorTestClass>();

    AActor* DummyActor = NewObject<AActor>();
    DummyActor->SetActorLocation(FVector(100.f, 200.f, 300.f));

    TestActor->TargetActor = DummyActor;

    FVector ExpectedLocation = DummyActor->GetActorLocation();

    FVector ActualLocation = TestActor->GetTargetActorLocation();

    TestEqual(TEXT("Equal?"), ActualLocation, ExpectedLocation);

    return true;
}