// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthBarWidget.h"




void UEnemyHealthBarWidget::UpdateHealth(float NewHealth)
{
	CurrentHealth = NewHealth;
	PercentHealth = CurrentHealth / MaxHealth;
}

void UEnemyHealthBarWidget::SetupHealth(float CurrentHealth, float MaxHealth)
{
	this->CurrentHealth = CurrentHealth;
	this->MaxHealth = MaxHealth;
	PercentHealth = CurrentHealth / MaxHealth;
}