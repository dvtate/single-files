// https://www.hackerrank.com/challenges/attending-workshops
#include <vector>
#include <algorithm>

//Define the structs Workshop and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop {
    int start, duration, end;
};
struct Available_Workshops {
    int n;
    std::vector<Workshop> shops;
};

Available_Workshops* initialize(int starts[], int durations[], int n) {
   Available_Workshops* ret = new Available_Workshops;
   ret->n = n;
   ret->shops.resize(n);
   int i = 0;
   for (auto& ws : ret->shops){
       ws.start = starts[i];
       ws.duration = durations[i];
       ws.end = starts[i] + durations[i];
       i++;
   }
    
    return ret;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)                            
{                                                                              
  int max_ws = 1;                                                    
  int no_ws = ptr->n;                                                 
  auto wrkshps = ptr->shops;
    
  sort(wrkshps.begin(), wrkshps.begin() + no_ws);                                                
  Workshop prev = wrkshps[0];
  for (int itr=1 ; itr<no_ws; itr++)                                           
  {                                                                            
    Workshop current = wrkshps[itr];                                           
    if (current.start >= prev.end)                                             
    {                                                                          
      max_ws++;                                                                
      prev = current;                                                          
    }                                                                          
  }                                                                            
  return max_ws;                                                               
}                                                                              


bool operator<(Workshop const & a, Workshop const & b)                         
{                                                                              
      return a.end < b.end;                                                    
} 

