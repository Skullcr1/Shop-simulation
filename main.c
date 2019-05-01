#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
#include <unistd.h>
#include "header.h"
#include "ilgas.h"
#include <time.h>
#define CostumerNumberMAX 20;
#define WorkTime 480;
/* Program to test DequeFunctions.c*/
int RandomCostumerNumber(int Probability, struct Node *shelf);
struct Node *AddToShelf(int CostumerNumber, struct Node *shelf);
char *extraTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2);
int DocumentAmount(int HandleTime, int CostumerNumber);
void printCommunicator();
void CheckHowBusy(int ApproxWorkTime, int handleTime);
void customerStatus(int CustomerNumber, int DocNumber);
void DestroyIlgas(ManoIlgas integer, ManoIlgas integer1);
void test(ManoIlgas speedx1, ManoIlgas speedx2, ManoIlgas result, struct Node* shelf, int eff2);
int main()
{
  time_t t;
  srand((unsigned)time(&t));
  struct Node *shelf = initializeDeque();
  int EfficiencyX1, EfficiencyX2, Probability, HandleTime;
  int CostumerNumber, DailyWorkTime;
  int WorkPercentage;
  int ApproxWorkTime;
  ManoIlgas ExtraWorkTime;
  ManoIlgas DailyWorkTime1;
  printf("********************\nCommission simulator\n********************\n");
  printf("Commisions work time - 8 hours(480 minutes).\n");
  printf("Commision employees review documents after work.\n");
  printf("Aim of the simulation: extra time spent to take care of documents and .\n");
  sleep(2);
  printf("Enter time of dealing with 1 customer (in minutes):");
  scanf("%d", &HandleTime);
  printf("Enter probability of customer arrival (0 - 100%):");
  scanf("%d", &Probability);
  printf("Enter productivity (n/hour):\n");
  printf("Office worker nr.1: ");
  scanf("%d", &EfficiencyX1);
  printf("Office worker nr.2: ");
  scanf("%d", &EfficiencyX2);
  CostumerNumber = RandomCostumerNumber(Probability, shelf);
  int docAmount = DocumentAmount(HandleTime, CostumerNumber);
  customerStatus(CostumerNumber, docAmount);
  sleep(1);
  struct Node *deque = AddToShelf(docAmount, shelf);
  char *c;
  printf("Working time has ended. Time to review documents\n");
  c = extraTime(CostumerNumber, deque, EfficiencyX1, EfficiencyX2);
  printf("\n");
  CheckHowBusy(docAmount, HandleTime);
  printf("Amount of costumers:%d\n", CostumerNumber);
  printf("Amount of accepted documents:%d\n", docAmount);
  printf("Time to deal with documents:%s minutes\n", c);
  removeDeque(&deque);
  removeDeque(&shelf);
  return 0;
}

void printCommunicatorX1()
{
  printf("Document accomplished by office worker nr.1. \n");
  sleep(1);
}
void printCommunicatorX2()
{
  printf("Document accomplished by office worker nr.2. \n");
  sleep(1);
}
void printCommunicator()
{
  printf("Document accomplished. \n");
  sleep(1);
}

void customerStatus(int CustomerNumber, int DocNumber)
{
  for (int i = 0; i < CustomerNumber; i++)
  {
    sleep(1);
    printf("New customer arrived.\n");
    if (DocNumber != 0)
    {
      int d = i + 1;
      sleep(1);
      printf("Costumer %d accepted.\n", d);
      DocNumber = DocNumber - 1;
    }
    else
    {
      printf("Costumer will not be accepted today.\n");
    }
  }
}

int RandomCostumerNumber(int Probability, struct Node *shelf)
{
  int max = CostumerNumberMAX;
  int CostumerNumber = 0;
  int Chance;
  for (int i = 0; i < max; i++)
  {
    Chance = (rand() % 101);
    if (Chance <= Probability)
    {
      CostumerNumber = CostumerNumber + 1;
    }
    // CostumerNumber = CostumerNumber + 1;
  }
  printf("\n");
  return CostumerNumber;
}

int DocumentAmount(int HandleTime, int CostumerNumber)
{
  int DailyWorkTime = WorkTime;
  int ApproxWorkTime = HandleTime * CostumerNumber;
  if (ApproxWorkTime > DailyWorkTime)
  {
    while (ApproxWorkTime > DailyWorkTime)
    {
      CostumerNumber = CostumerNumber - 1;
      ApproxWorkTime = HandleTime * CostumerNumber;
    }
  }
  return CostumerNumber;
}

struct Node *AddToShelf(int CostumerNumber, struct Node *shelf)
{
  for (int i = 0; i < CostumerNumber; i++)
  {
    addFront(&shelf, 1);
  }
  return shelf;
}

char *extraTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2)
{
  int minutesX1 = 60 / EfficiencyX1;
  int minutesX2 = 60 / EfficiencyX2;
  int minutes = 0, eff1, eff2;
  eff2 = EfficiencyX2 / EfficiencyX1;
  eff1 = EfficiencyX1 / EfficiencyX2;
  ManoIlgas speedx1;
  ManoIlgas speedx2;
  ManoIlgas result;
  char speed1[100];
  char speed2[100];
  char resultx[100];
  sprintf(speed1, "%d", minutesX1);
  sprintf(speed2, "%d", minutesX2);
  Str2Ilgas(&result, "0");
  Str2Ilgas(&speedx1, speed1);
  Str2Ilgas(&speedx2, speed2);
  if (CostumerNumber == 1)
  {
    int Chance = rand() % 2;
    if (Chance == 1)
    {
      removeDeque(&shelf);
      printCommunicatorX1();
      return Ilgas2Str(speedx1);
    }
    else
    {
      removeDeque(&shelf);
      printCommunicatorX2();
      return Ilgas2Str(speedx2);
    }
  }
  if (minutesX1 == minutesX2)
  {
    while (isDequeEmpty(&shelf) != 2)
    {
      // printCommunicator();
      // delFront(&shelf);
      // Iadd(speedx1, result, &result);
     test(speedx1,speedx2,result,shelf,eff2);
    }
    DestroyIlgas(speedx2, speedx1);
    return Ilgas2Str(result);
  }
  if (EfficiencyX1 < EfficiencyX2)
  {
    if ((EfficiencyX2 % EfficiencyX1) == 0)
    {
      while (isDequeEmpty(&shelf) != 2)
      {
        printf("\n");
        for (int i = 0; i < 1; i++)
        {
          Iadd(speedx1, result, &result);
          delFront(&shelf);
          printCommunicatorX1(i);
        }
        for (int i = 0; i < eff2; i++)
        {
          if (isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx2, result, &result);
            delRear(&shelf);
            printCommunicatorX2(i);
          }
        }
      }
      DestroyIlgas(speedx2, speedx1);
      return Ilgas2Str(result);
    }
    if ((EfficiencyX2 % EfficiencyX1) != 0)
    {
      if ((EfficiencyX2 / EfficiencyX1 == 1))
      {
        while (isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for (int i = 0; i < 1; i++)
          {
            Iadd(speedx1, result, &result);
            delFront(&shelf);
            printCommunicatorX1();
          }
          for (int i = 0; i < 2; i++)
          {
            if (isDequeEmpty(&shelf) != 2)
            {
              Iadd(speedx2, result, &result);
              delRear(&shelf);
              printCommunicatorX2();
            }
          }
        }
        DestroyIlgas(speedx2, speedx1);
        return Ilgas2Str(result);
      }
      else
      {
        delRear(&shelf);
        printCommunicatorX2();
        Iadd(speedx2, result, &result);
        while (isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for (int i = 0; i < eff2; i++)
          {
            Iadd(speedx2, result, &result);
            delRear(&shelf);
            printCommunicatorX2();
          }
          for (int i = 0; i < 1; i++)
          {
            Iadd(speedx1, result, &result);
            delFront(&shelf);
            printCommunicatorX1();
          }
        }
        DestroyIlgas(speedx2, speedx1);
        return Ilgas2Str(result);
      }
    }
  }
  if (EfficiencyX1 > EfficiencyX2)
  {
    if ((EfficiencyX1 % EfficiencyX2) == 0)
    {
      while (isDequeEmpty(&shelf) != 2)
      {
        printf("\n");
        for (int i = 0; i < 1; i++)
        {
          Iadd(speedx2, result, &result);
          delFront(&shelf);
          printCommunicatorX2();
        }
        for (int i = 0; i < eff2; i++)
        {
          if (isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx1, result, &result);
            delRear(&shelf);
            printCommunicatorX1();
          }
        }
      }
      DestroyIlgas(speedx2, speedx1);
      return Ilgas2Str(result);
    }
    if ((EfficiencyX1 % EfficiencyX2) != 0)
    {
      if ((EfficiencyX1 / EfficiencyX2 == 1))
      {
        while (isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for (int i = 0; i < 1; i++)
          {
            Iadd(speedx2, result, &result);
            delFront(&shelf);
            printCommunicatorX2();
          }
          for (int i = 0; i < 2; i++)
          {
            if (isDequeEmpty(&shelf) != 2)
            {
              Iadd(speedx1, result, &result);
              delRear(&shelf);
              printCommunicatorX1();
            }
          }
        }
        DestroyIlgas(speedx2, speedx1);
        return Ilgas2Str(result);
      }
      else
      {
        delRear(&shelf);
        printCommunicatorX1();
        Iadd(speedx1, result, &result);
        while (isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for (int i = 0; i < eff1; i++)
          {
            Iadd(speedx1, result, &result);
            delRear(&shelf);
            printCommunicatorX1();
          }
          for (int i = 0; i < 1; i++)
          {
            Iadd(speedx2, result, &result);
            delFront(&shelf);
            printCommunicatorX2();
          }
        }
        DestroyIlgas(speedx2, speedx1);
        return Ilgas2Str(result);
      }
    }
  }
}

void CheckHowBusy(int CostumerNumber, int handleTime)
{
  float number = CostumerNumber;
  float hTime = handleTime;
  float percents = ((number * hTime) * 100) / 480;
  printf("Busy:%.2f%\n", (int)(percents * 100) / 100.0);
}

void DestroyIlgas(ManoIlgas integer, ManoIlgas integer1)
{
  freeIlgas(&integer);
  freeIlgas(&integer1);
}
void test(ManoIlgas speedx1, ManoIlgas speedx2, ManoIlgas result, struct Node* shelf, int eff2){
printf("\n");
        for (int i = 0; i < 1; i++)
        {
          Iadd(speedx1, result, &result);
          delFront(&shelf);
          printCommunicatorX1(i);
        }
        for (int i = 0; i < eff2; i++)
        {
          if (isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx2, result, &result);
            delRear(&shelf);
            printCommunicatorX2(i);
          }
        }
}