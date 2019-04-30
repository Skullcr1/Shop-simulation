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
int ExtraWorkingTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2);
char *extraTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2);
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
  printf("Enter time of dealing with customers:");
  // scanf("%d", &HandleTime);
  printf("Enter probability:");
  // scanf("%d", &Probability);
  // CostumerNumber = RandomCostumerNumber(Probability, shelf);
  printf("\n");
  // struct Node* deque= AddToShelf(CostumerNumber,shelf);
  struct Node* deque= AddToShelf(10,shelf);

  // printDeque(deque);
  int test = ExtraWorkingTime(2,deque,2,5);
  // printf("%d :",test);
  // int docAmount = DocumentAmount(HandleTime, CostumerNumber);
  char *c;
  c = extraTime(2,deque,2,5);
  // printf("%s",c);
  // struct Node *deque = test(shelf);
  // addFront(&deque, 1);
  // printDeque(deque);
  // Str2Ilgas(&DailyWorkTime1, "480"); //8 hours to minutes
  // printf("%s",c);
  // printf("%s",Ilgas2Str(DailyWorkTime1));
  return 0; 
  
} 

/*

// pthread_t thread_id; 
    // printf("Before Thread\n"); 
    // pthread_create(&thread_id, NULL, myThreadFun, NULL); 
    // pthread_join(thread_id, NULL); 
    // printf("After Thread\n"); 
    // exit(0); 



  // void *myThreadFun(void *vargp) 
  // {
    
  //   printf("Printing GeeksQuiz from Thread \n"); 
  //   sleep(1);
  //   printf("Printing \n"); 
  //   return NULL; 
  // }
*/

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
        printf("New costumer arrived.\n");
        sleep(1);
        // addFront(&shelf, 1);
        // AddToShelf(1,shelf);
      }
    }
    printf("\n");
    // printDeque(shelf);
    return CostumerNumber;
  }


// int DocumentAmount(int HandleTime, int CostumerNumber)
//   {
//     int DailyWorkTime = WorkTime;
//     int ApproxWorkTime = HandleTime * CostumerNumber;
//     if(ApproxWorkTime > DailyWorkTime)
//     {
//       while(ApproxWorkTime > DailyWorkTime)
//       {
//         CostumerNumber = CostumerNumber - 1;
//         ApproxWorkTime = HandleTime * CostumerNumber;
//       }
//     }
//     return ApproxWorkTime;
//   }

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
      return Ilgas2Str(speedx1);
    }
    else
    {
      removeDeque(&shelf);
      return Ilgas2Str(speedx2);
    }
  }
  if(minutesX1 == minutesX2)
  {
    while(isDequeEmpty(&shelf) != 2)
    {
      delFront(&shelf);
      Iadd(speedx1,result,&result);
    }
    return Ilgas2Str(result);
  }
  if(EfficiencyX1 < EfficiencyX2)
  {
    if((EfficiencyX2 % EfficiencyX1) == 0)
    {
      printf("modulis\n");
      while(isDequeEmpty(&shelf) != 2)
      { 
        printDeque(shelf);
        printf("\n");
        printf("inside of loop\n");
        for(int i = 0; i < 1; i++)
        {
          Iadd(speedx1,result,&result);
          delFront(&shelf);
          printf("%d\n",minutes);
        }
        for(int i = 0; i < eff2; i++)
        {
          if(isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx2,result,&result);
            delRear(&shelf);
            printf("%d\n",minutes);
          }
        }
      }
      return Ilgas2Str(result);
    }
    if((EfficiencyX2 % EfficiencyX1) != 0)
    {
      if((EfficiencyX2/EfficiencyX1 == 1))
      {
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          printf("inside of loop\n");
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx1,result,&result);
            delFront(&shelf);
            printf("%d\n",minutes);
          }
          for(int i = 0; i < 2; i++)
          {
            if(isDequeEmpty(&shelf) != 2)
            {
              Iadd(speedx2,result,&result);
              delRear(&shelf);
              printf("%d\n",minutes);
            }
          }
        }
        return Ilgas2Str(result);
      }
      else 
      {
        delRear(&shelf);
        Iadd(speedx2,result,&result);
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          printf("inside of loop\n");
          for(int i = 0; i < eff2; i++)
          {
            Iadd(speedx2,result,&result);
            delRear(&shelf);
            printf("%d\n",minutes);
          }
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx1,result,&result);
            delFront(&shelf);
            printf("%d\n",minutes);
          }
        }
        return Ilgas2Str(result);
      }
    }
  }
  if(EfficiencyX1 > EfficiencyX2)
  {
    if((EfficiencyX1 % EfficiencyX2) == 0)
    {
      printf("modulis\n");
      while(isDequeEmpty(&shelf) != 2)
      { 
        printDeque(shelf);
        printf("\n");
        printf("inside of loop\n");
        for(int i = 0; i < 1; i++)
        {
          Iadd(speedx2,result,&result);
          delFront(&shelf);
          printf("%d\n",minutes);
        }
        for(int i = 0; i < eff2; i++)
        {
          if(isDequeEmpty(&shelf) != 2)
          {
            Iadd(speedx1,result,&result);
            delRear(&shelf);
            printf("%d\n",minutes);
          }
        }
      }
      return Ilgas2Str(result);
    }
    if((EfficiencyX1 % EfficiencyX2) != 0)
    {
      if((EfficiencyX1/EfficiencyX2 == 1))
      {
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          printf("inside of loop\n");
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx2,result,&result);
            delFront(&shelf);
            printf("%d\n",minutes);
          }
          for(int i = 0; i < 2; i++)
          {
            if(isDequeEmpty(&shelf) != 2)
            {
              Iadd(speedx1,result,&result);
              delRear(&shelf);
              printf("%d\n",minutes);
            }
          }
        }
        return Ilgas2Str(result);
      }
      else 
      {
        delRear(&shelf);
        Iadd(speedx1,result,&result);
        while(isDequeEmpty(&shelf) != 2)
        {
          printf("\n");
          printf("inside of loop\n");
          for(int i = 0; i < eff1; i++)
          {
            Iadd(speedx1,result,&result);
            delRear(&shelf);
            printf("%d\n",minutes);
          }
          for(int i = 0; i < 1; i++)
          {
            Iadd(speedx2,result,&result);
            delFront(&shelf);
            printf("%d\n",minutes);
          }
        }
        return Ilgas2Str(result);
      }
    }
  }
}



//   int CheckHowBusy(int ApproxWorkTime)
//   {
//     int percents = (ApproxWorkTime*100)/480;
//     return percents;
//   }







// int ExtraWorkingTime(int CostumerNumber, struct Node *shelf, int EfficiencyX1, int EfficiencyX2)
// {
//   int minutesX1 = 60/EfficiencyX1;
//   int minutesX2 = 60/EfficiencyX2;
//   int minutes = 0, eff1, eff2;
//   eff2 = EfficiencyX2/EfficiencyX1;


//   if(CostumerNumber == 1)
//   {
//     int Chance = rand() %2;
//     if(Chance == 1)
//     {
//       removeDeque(&shelf);
//       return minutesX1;
//     }
//     else
//     {
//       removeDeque(&shelf);
//       return minutesX2;
//     }
//   }
//   if(minutesX1 == minutesX2)
//   {
//     while(isDequeEmpty(&shelf) != 2)
//     {
//       delFront(&shelf);
//       minutes = minutesX1 + minutes;
//     }
//     return minutes;
//   }
//   if(EfficiencyX1 < EfficiencyX2)
//   {
//     if((EfficiencyX2 % EfficiencyX1) == 0)
//     {
//     printf("modulis\n");

//       while(isDequeEmpty(&shelf) != 2)
//       { 
//         printDeque(shelf);
//         printf("\n");
//         printf("inside of loop\n");
//         for(int i = 0; i < 1; i++)
//         {
//           minutes = minutesX1 + minutes;
//           delFront(&shelf);
//           printf("%d\n",minutes);

//         }
//         for(int i = 0; i < eff2; i++)
//         {
//           if(isDequeEmpty(&shelf) != 2)
//           {
//             minutes = minutesX2 + minutes;
//             delRear(&shelf);
//             printf("%d\n",minutes);
//           }
//         }
//       }
//       return minutes;
//     }
//     if((EfficiencyX2 % EfficiencyX1) != 0)
//     {
//       if((EfficiencyX2/EfficiencyX1 == 1))
//       {
//         while(isDequeEmpty(&shelf) != 2)
//         {
//          printf("\n");
//         printf("inside of loop\n");
//             for(int i = 0; i < 1; i++)
//             {
//               minutes = minutesX1 + minutes;
//               delFront(&shelf);
//               printf("%d\n",minutes);

//             }
//             for(int i = 0; i < 2; i++)
//             {
//               if(isDequeEmpty(&shelf) != 2)
//               {
//                 minutes = minutesX2 + minutes;
//                 delRear(&shelf);
//                 printf("%d\n",minutes);
//               }
//             }
//         }
//       return minutes;
//       }
//       else 
//       {
//         delRear(&shelf);
//         minutes = minutesX2 + minutes;
//         while(isDequeEmpty(&shelf) != 2)
//         {
//           printf("\n");
//         printf("inside of loop\n");
//           for(int i = 0; i < eff2; i++)
//           {
//             minutes = minutesX2 + minutes;
//             delRear(&shelf);
//             printf("%d\n",minutes);
//           }
//           for(int i = 0; i < 1; i++)
//           {
//             minutes = minutesX1 + minutes;
//             delFront(&shelf);
//             printf("%d\n",minutes);
//           }
//         }
//         return minutes;
//       }
      
//   }

// }
// }





