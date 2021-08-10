#include<iostream>
#include<cstdlib>
#include <sys/time.h>

struct myOUTCOME{
  bool flag;
  int type;
};

long getCurrentTime()  
{  
   struct timeval tv;  
   gettimeofday(&tv,NULL);  
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;  
}

void outputTips(const int typeFlag, const int n_1, const int n_2)
{
  switch (typeFlag)
  {
  default:
  case 1:
    std::cout << n_1 << " + " << n_2 << " = ";
    break;
  case 2:
    std::cout << n_1 << " - " << std::abs(n_2) << " = ";
    break;
  case 3:
    std::cout << n_1 << " * " << n_2 << " = ";
    break;
  case 4:
    std::cout << n_1 << " / " << std::abs(n_2) << " = ";
    break;
  }
}

int getAnswer(const int typeFlag, const int n_1, const int n_2)
{
  switch (typeFlag)
  {
  default:
  case 1:
    return (int) n_1 + n_2;
    break;
  case 2:
    return (int) n_1 - std::abs(n_2);
    break;
  case 3:
    return (int) n_1 * n_2;
    break;
  case 4:
    return (int) n_1 / std::abs(n_2);
    break;
  }
}

void practice(const int n, const int range, const int typeFlag)
{
  int ans;
  long init_time, end_time, sum_time = 0, min_time = 10000000000;
  float score;
  int  num_1[n], num_2[n];
  myOUTCOME outcomes[n];

  for(int i = 0; i < n; i++){
    srand((unsigned)time(NULL));
    num_1[i] = std::rand()%range;
    num_2[i] = std::rand()%(2*range) - range;
    
    switch (typeFlag)
    {
    default:
    case 1: // 加减法
      if(num_2[i] >= 0){
        outcomes[i].type = 1; // 加法
      }
      else{
        outcomes[i].type = 2; // 减法
      }
      break;
    case 2: // 乘除法
      if(num_2[i] >= 0){
        outcomes[i].type = 3; // 乘法
      }
      else{
        outcomes[i].type = 4; // 除法
      }
      break;
    }

    outputTips(outcomes[i].type, num_1[i], num_2[i]);

    init_time = getCurrentTime();
    std::cin >> ans;
    end_time = getCurrentTime();
    sum_time += end_time - init_time;
    if(min_time > end_time - init_time){
      min_time = end_time - init_time;
    }
    std::cout << "平均用时： " << (long)(sum_time/(i+1)) << "ms" << std::endl;
    std::cout << "最短用时： " << min_time << "ms" << std::endl;
    
    if(ans == getAnswer(outcomes[i].type, num_1[i], num_2[i])){
      outcomes[i].flag = 1;
      score += 1.0;
    }
    else{
      outcomes[i].flag = 0;
    }
  }

  std::cout << "答对题目数目: " << (int)score << std::endl;
  std::cout << "答错题目数目： " << (int)(n - score) << std::endl;
  std::cout << "最终得分: " << (int)(score/n*100) << std::endl;
  if((int)(score/n*100) < 100){
    std::cout << "回答错误的题目： " << std::endl;
    for(int j = 0; j < n; j++){
      if(!outcomes[j].flag){
        outputTips(outcomes[j].type, num_1[j], num_2[j]);
        std::cout << getAnswer(outcomes[j].type, num_1[j], num_2[j]) << std::endl;
      }
    }
  }
}

int main(){
  int n, range, typeFlag;
  do{
    std::cout << "请选择运算类型，1：加减法; 2：乘除法： " << std::endl;
    std::cin >> typeFlag;
    if(typeFlag < 1 || typeFlag > 2){
      std::cout << "输入类型有误，请选择1或2！" << std::endl;
      continue;
    }
    std::cout << "请输入题目数量： ";
    std::cin >> n;
    if(n <= 0){
      std::cout << "输入数目有误，请输入大于0的整数！" << std::endl;
      continue;
    }
    std::cout << "请输入数据范围： ";
    std::cin >> range;
    if(range <= 0){
      std::cout << "输入范围有错，请输入大于0的整数！" << std::endl;
      continue;
    }
  }while(n <= 0 || range <= 0 || typeFlag < 1 || typeFlag > 2);
  std::cout << "共有" << n << "道题目" << std::endl;
  std::cout << "答案请输入整数部分，忽略小数！" << std::endl;
  
  practice(n, range, typeFlag);

  return 0;
}