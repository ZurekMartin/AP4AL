/*!
 * \file       list.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementing functions of ATD list defined in a header file
 * list.h
 * ****************************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "list.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
void List_Init(List_t *const list)
{
  if (list == NULL)
  {
    return;
  }

  list->active = NULL;
  list->first = NULL;
}

void List_Insert_First(List_t *const list, Data_t data)
{
  if (!list)
  {
    return;
  }

  List_Node_t  *node = myMalloc(sizeof(List_Node_t));
  if (!node)
  {
    return;
  }

  node->data = data;
  node->next = list->first;
  list->first = node;
}

void List_First(List_t *const list)
{
  if (!list)
  {
    return;
  }

  list->active = list->first;
}

bool List_Copy_First(List_t list, Data_t *data)
{
  if (!data || !list.first)
  {
    return false;
  }

  *data = list.first->data;

  return true;
}

void List_Delete_First(List_t *const list)
{
  if (!list || !list->first)
  {
    return;
  }

  List_Node_t *node = list->first;
  list->first = list->first->next;
  myFree(node);

  if (list->active == node)
  {
    list->active = NULL;
  }
}

void List_Post_Delete(List_t *const list)
{
  if (!list || !list->active || !list->active->next)
  {
    return;
  }

  List_Node_t *node = list->active->next;
  list->active->next = list->active->next->next;
  myFree(node);
}

void List_Post_Insert(List_t *const list, Data_t data)
{
  if (!list || !list->active)
  {
    return;
  }

  List_Node_t *node = myMalloc(sizeof(List_Node_t));
  if (!node)
  {
    return;
  }

  node->data = data;
  node->next = list->active->next;
  list->active->next = node;
}

bool List_Copy(List_t list, Data_t *data)
{
if (!data || !list.active)
  {
    return false;
  }

  *data = list.active->data;

  return true;
}

void List_Active_Update(const List_t *const list, Data_t data)
{
  if (!list || !list->active)
  {
    return;
  }

  list->active->data = data;
}

void List_Active_Next(List_t *const list)
{
  if (!list || !list->active)
  {
    return;
  }

  list->active = list->active->next;
}

bool List_Is_Active(List_t list)
{
  if (list.active)
  {
    return true;
  } else {
    return false;
  }
}

// Pridany kod pro testovani funkce Merge
void Merge(List_t *vysledek, List_t *seznam1, List_t *seznam2) {
  List_First(seznam1);
  List_First(seznam2);

  while (List_Is_Active(*seznam1) && List_Is_Active(*seznam2)) {
    Data_t data1, data2;
    List_Copy(*seznam1, &data1);
    List_Copy(*seznam2, &data2);

    if (Data_Cmp(&data1, &data2) < 0) {
      List_Insert_First(vysledek, data1);
      List_Active_Next(seznam1);
    } else {
      List_Insert_First(vysledek, data2);
      List_Active_Next(seznam2);
    }
  }

  while (List_Is_Active(*seznam1)) {
    Data_t data;
    List_Copy(*seznam1, &data);
    List_Insert_First(vysledek, data);
    List_Active_Next(seznam1);
  }

  while (List_Is_Active(*seznam2)) {
    Data_t data;
    List_Copy(*seznam2, &data);
    List_Insert_First(vysledek, data);
    List_Active_Next(seznam2);
  }
}

/* Private function definitions ------------------------------------------------------------------*/
