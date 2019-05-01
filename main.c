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
struct Node* AddToShelf(int CostumerNumber, struct Node *shelf);
// void *myThreadFun(void *vargp) ;
struct Node* test(struct Node *shelf);
// int ExtraWorkingTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2);
char *extraTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2);
int DocumentAmount(int HandleTime, int CostumerNumber);
void printCommunicator();
void CheckHowBusy(int ApproxWorkTime, int handleTime);
void customerStatus(int CustomerNumber, int DocNumber);
void DestroyIlgas(ManoIlgas integer, ManoIlgas integer1);
int main() 
{ 
  
  time_t t;
  srand((unsigned) time(&t));
  struct Node *shelf = initializeDeque();
  int EfficiencyX1, EfficiencyX2, Probability, HandleTime;
  int CostumerNumber, DailyWorkTime;
  int WorkPercentage;
  int ApproxWorkTime;
  ManoIlgas ExtraWorkTime;
  ManoIlgas DailyWorkTime1;
  printf("********************\nCommission simulator\n********************\n");
  printf("Commision starts work at 8 AM and closes at 4 PM (lunch brake not included).\n");
  printf("Commision employees review documents after work.\n");
  sleep(4);
  printf("Enter time of dealing with customers:");
  scanf("%d", &HandleTime);
  printf("Enter probability:");
  scanf("%d", &Probability);
  printf("Enter productivity (n/hour):\n");
  printf("Office worker nr.1: ");
  scanf("%d",&EfficiencyX1);
  printf("Office worker nr.2: ");
  scanf("%d",&EfficiencyX2);
  CostumerNumber = RandomCostumerNumber(Probability, shelf);
  int docAmount = DocumentAmount(HandleTime, CostumerNumber);
  printf("\n");
  // CostumerNumber = docAmount;
  customerStatus(CostumerNumber,docAmount);
  sleep(1);
  struct Node* deque= AddToShelf(docAmount,shelf);
  char *c;
  c = extraTime(CostumerNumber,deque,EfficiencyX1,EfficiencyX2);
  CheckHowBusy(docAmount,HandleTime);
  
  printf("Time to deal with documents:%s minutes\n",c);

  removeDeque(&deque);
  removeDeque(&shelf);
  
  return 0; 
} 


void printCommunicator()
{

  printf("Document accomplished. \n");
  sleep(1);
  
}

void customerStatus(int CustomerNumber, int DocNumber)
{
  for(int i = 0; i < CustomerNumber; i++)
  {
    sleep(1);
    printf("New customer arrived.\n");
    if(DocNumber != 0)
    {
      sleep(1);
      printf("Costumer accepted.\n");
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
    for(int i = 0; i < max; i++)
    {
      Chance = (rand() % 101);
      if(Chance <= Probability)
      {
        CostumerNumber = CostumerNumber + 1;
      }
    }
    printf("\n");
    return CostumerNumber;
  }


int DocumentAmount(int HandleTime, int CostumerNumber)
  {
    int DailyWorkTime = WorkTime;
    int ApproxWorkTime = HandleTime * CostumerNumber;
    if(ApproxWorkTime > DailyWorkTime)
    {
      while(ApproxWorkTime > DailyWorkTime)
      {
        CostumerNumber = CostumerNumber - 1;
        ApproxWorkTime = HandleTime * CostumerNumber;
      }
    }
    return CostumerNumber;
  }

struct Node* AddToShelf(int CostumerNumber,struct Node *shelf )
  {
  for(int i = 0; i < CostumerNumber; i++)
  {
    addFront(&shelf,1);
  }
  return shelf;
  }

char *extraTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2)
{
  int minutesX1 = 60/EfficiencyX1;
  int minutesX2 = 60/EfficiencyX2;
  int minutes = 0, eff1, eff2;
  eff2 = EfficiencyX2/EfficiencyX1;
  eff1 = EfficiencyX1/EfficiencyX2;
  ManoIlgas speedx1;
  ManoIlgas speedx2;
  ManoIlgas result;
  char speed1[100];
  char speed2[100];
  char resultx[100];
  sprintf(speed1, "%d",minutesX1);
  sprintf(speed2, "%d",minutesX2);
  Str2Ilgas(&result,"0");
  Str2Ilgas(&speedx1,speed1);
  Str2Ilgas(&speedx2, speed2);
  if(CostumerNumber == 1)
  {
    int Chance = rand() %2;
    if(Chance == 1)
    {
      removeDeque(&shelf);
      printCommunicator();
      return Ilgas2Str(speedx1);
    }
    else
    {
      removeDeque(&shelf);
      printCommunicator();
      return Ilgas2Str(speedx2);
    }
  }
  if(minutesX1 == minutesX2)
  {
    while(isDequeEmpty(&shelf) != 2)
    {
      printCommunicator();
      delFront(&shelf);
      Iadd(speedx1,result,&result);
    }
    DestroyIlgas(speedx2,speedx1);
    return Ilgas2Str(result);
  }
  if(EfficiencyX1 < EfficiencyX2)
  {
    if((EfficiencyX2 % EfficiencyX1) == 0)
    {
      while(isDequeEmpty(&shelf) != 2)
      { 
        printDeque(shelf);
        printf("\n");
        for(int i = 0; i < 1; i++)
        {
          Iadd(speedx1,result,&result);
          delFront(&shelf);
          printCommunicator();
        }
        for(int i = 0; i < eff2; i++)
        {
          if(isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx2,result,&result);
            delRear(&shelf);
            printCommunicator();
          }
        }
      }
      DestroyIlgas(speedx2,speedx1);
      return Ilgas2Str(result);
    }
    if((EfficiencyX2 % EfficiencyX1) != 0)
    {
      if((EfficiencyX2/EfficiencyX1 == 1))
      {
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx1,result,&result);
            delFront(&shelf);
            printCommunicator();
          }
          for(int i = 0; i < 2; i++)
          {
            if(isDequeEmpty(&shelf) != 2)
            {
              Iadd(speedx2,result,&result);
              delRear(&shelf);
              printCommunicator();
            }
          }
        }
        DestroyIlgas(speedx2,speedx1);
        return Ilgas2Str(result);
      }
      else 
      {
        delRear(&shelf);
        printCommunicator();
        Iadd(speedx2,result,&result);
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for(int i = 0; i < eff2; i++)
          {
            Iadd(speedx2,result,&result);
            delRear(&shelf);
            printCommunicator();
          }
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx1,result,&result);
            delFront(&shelf);
            printCommunicator();
          }
        }
        DestroyIlgas(speedx2,speedx1);
        return Ilgas2Str(result);
      }
    }
  }
  if(EfficiencyX1 > EfficiencyX2)
  {
    if((EfficiencyX1 % EfficiencyX2) == 0)
    {
      while(isDequeEmpty(&shelf) != 2)
      { 
        printDeque(shelf);
        printf("\n");
        for(int i = 0; i < 1; i++)
        {
          Iadd(speedx2,result,&result);
          delFront(&shelf);
          printCommunicator();
        }
        for(int i = 0; i < eff2; i++)
        {
          if(isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx1,result,&result);
            delRear(&shelf);
            printCommunicator();
          }
        }
      }
      DestroyIlgas(speedx2,speedx1);
      return Ilgas2Str(result);
    }
    if((EfficiencyX1 % EfficiencyX2) != 0)
    {
      if((EfficiencyX1/EfficiencyX2 == 1))
      {
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx2,result,&result);
            delFront(&shelf);
            printCommunicator();
          }
          for(int i = 0; i < 2; i++)
          {
            if(isDequeEmpty(&shelf) != 2)
            {
              Iadd(speedx1,result,&result);
              delRear(&shelf);
              printCommunicator();
            }
          }
        }
        DestroyIlgas(speedx2,speedx1);
        return Ilgas2Str(result);
      }
      else 
      {
        delRear(&shelf);
        printCommunicator();
        Iadd(speedx1,result,&result);
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          for(int i = 0; i < eff1; i++)
          {
            Iadd(speedx1,result,&result);
            delRear(&shelf);
            printCommunicator();
          }
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx2,result,&result);
            delFront(&shelf);
            printCommunicator();
          }
        }
        DestroyIlgas(speedx2,speedx1);
        return Ilgas2Str(result);
      }
    }
  }
}



  void CheckHowBusy(int CostumerNumber, int handleTime)
  {
    float number = CostumerNumber;
    float hTime = handleTime;
    float percents = ((number*hTime)*100)/480;
    printf("Busy:%.2f%\n",(int)(percents*100)/100.0);
  }

  void DestroyIlgas(ManoIlgas integer, ManoIlgas integer1)
  {
    freeIlgas(&integer);
    freeIlgas(&integer1);
  }












