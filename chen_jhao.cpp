#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>
#include<functional>
#include<string>
#include <cstdio> 
#include<ctime>
 #include<Windows.h>
using namespace std;

typedef vector<vector<int>> T_Array;



T_Array read_csv_file(const char*);

T_Array join_csv(T_Array&, T_Array&, int, int);

vector<T_Array> group_sort_3D(T_Array&, int, int);

T_Array result_t_array(vector<T_Array>& ) ;





int main()
{
	 DWORD startTime = GetTickCount();
	//T_Array input1 = read_csv_file("/home/web/ztedatabase/input1.csv");
	T_Array input1 = read_csv_file("C:\\Users\\1\\Desktop\\input1_1.csv");
	//T_Array input2 = read_csv_file("/home/web/ztedatabase/input2.csv");
	T_Array input2 = read_csv_file("C:\\Users\\1\\Desktop\\input2_1.csv");

	T_Array res ;
	res.resize(input1.size());
	
	res= join_csv(input1, input2, 3, 3);
	
	input1.clear();
	input2.clear();
	
	vector<T_Array> group_3D = group_sort_3D(res, 1, 4);
	
	res.clear();

	T_Array final_array=result_t_array( group_3D);

	group_3D.clear();

	sort(final_array.begin(), final_array.end(), [](vector<int>& input1, vector<int>& input2) {
		if (input1[0] < input2[0])
		{
	    	return true;
		}
		else if (input1[0] > input2[0])
		{
			return false;
		}
		else 
		{
			if (input1[4] < input2[4])
			{
				return true;
			}
			else if (input1[4] > input2[4])
			{
				return false;
			}
			else 
			{
				if (input1[1] < input2[1])
				{
					return true;
				}
				else if (input1[1] > input2[1])
				{
					return false;
				}
				else 
				{
					return false;
				}
			}
		}
		});
		 DWORD endTime = GetTickCount();
	
	for (int i = 0;i <final_array.size();i++)	
		printf("%d,%d\n",final_array[i][0],final_array[i][3]);	
	final_array.clear();
     cout << "The run time is:" << endTime - startTime << "ms" << endl;
	return 0;
}

T_Array read_csv_file(const char* filename)
{
	ifstream inFile(filename, ios::in);
	string line;
	T_Array t_Array;
	while (getline(inFile, line))
	{		
		stringstream ss(line);
		string str;
		vector<int> v(0);
	
		
		while (getline(ss, str, ','))
		{
			v.push_back(atoi(str.c_str()));
		}
		t_Array.push_back(v);
	}

	return t_Array;
}

T_Array join_csv(T_Array& input1, T_Array& input2, int t1, int t2)
{
	int size1 = input1.size(); 
	int size2 = input2.size();
	T_Array joinRes{0};
	


	
	sort(input1.begin(), input1.end(), [](vector<int>& input1, vector<int>& input2) {
		return input1[2] < input2[2];
		});

	
	sort(input2.begin(), input2.end(), [](vector<int>& input1, vector<int>& input2) {
		return input1[2] < input2[2];
		});
							
		
	int i = 0, j = 0;

	
	int rightflag=0,leftflag=0;
	
	while (i < size1 && j < size2)
	{
		
		if(size1==i)
		{
			i=size1-1;
			j++;
			leftflag=1;
		}
		if(size2==j)
		{
			j=size2-1;
			i++;
			rightflag=1;	
		}
	
		
		if(input1[i][2] == input2[j][2])
		{
			vector<int> temp(0);
		
			temp.push_back(input1[i][0]); 
			temp.push_back(input1[i][1]); 
			temp.push_back(input1[i][2]); 
			temp.push_back(input2[j][0]); 
			temp.push_back(input2[j][1]); 
			temp.push_back(input2[j][2]); 
			
			
			joinRes.push_back(temp);
			
			j++;
		}
		else if (input1[i][2] < input2[j][2])
			{
				if(leftflag)
					break;
				i++;
			}
		else if (input1[i][2] > input2[j][2])
			{
				if(rightflag)
					break;
				j++;
			}
			
		
	}
	

	

	return joinRes;
}

vector<T_Array> group_sort_3D(T_Array& input, int t1, int t2)
{
	sort(input.begin(), input.end(), [](vector<int>& input1, vector<int>& input2)
		{
			if (input1[1] < input2[1])
			{
				return true;
			}
			else if (input1[1] > input2[1])
			{
				return false;
			}
			else 
			{
				if (input1[4] < input2[4])
				{
					return true;
				}
				else if (input1[4] > input2[4])
				{
					return false;
				}
				else 
				{
					return false;
				}
			}
		});
		


	vector<T_Array> res;
	T_Array temp;
	


	for (int i = 0;i < input.size();i++)
	{
		if (i == 0)
		{
			temp.push_back(input[i]);
		}
		else
		{
			if ((input[i - 1][t1] == input[i][t1]) &&
				(input[i - 1][t2] == input[i][t2]))
			{
				temp.push_back(input[i]);
			}
			else
			{
				res.push_back(temp);
				temp.clear();
				temp.push_back(input[i]);
			}
			if (i + 1 == input.size())
			{
				res.push_back(temp);
			}
		}

	}


	return res;
}

T_Array result_t_array(vector<T_Array>& group_3D) 
{
	T_Array resultarray;

	for(int i=0;i<group_3D.size();i++)
	{
		if(1==group_3D[i].size())
			resultarray.push_back(group_3D[i][0]);
		else
		{
			
			sort(group_3D[i].begin(),group_3D[i].end(), [](vector<int>& input1, vector<int>& input2) {
						return input1[0] > input2[0];
				});
	
		
		
	
	
	
	 		vector<int> v(0);
		
			v.push_back(group_3D[i][0][0]);	
			
	
			
			sort(group_3D[i].begin(),group_3D[i].end(), [](vector<int>& input1, vector<int>& input2) {
						return input1[3] < input2[3];
				});
	
	
				
			v.push_back(group_3D[i][0][1]);
			v.push_back(group_3D[i][0][2]);
			v.push_back(group_3D[i][0][3]);	
		
			
				
			v.push_back(group_3D[i][0][4]);
			v.push_back(group_3D[i][0][5]);
			
		
		   	resultarray.push_back(v);
			
		}
			
	}
		

	return resultarray;
}
