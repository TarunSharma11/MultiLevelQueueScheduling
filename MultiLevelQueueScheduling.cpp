#include<bits/stdc++.h> 		//sequential process
using namespace std;
typedef struct Time
{								//1 - > computation, 2 - > input/output
	int time,mode;
}t;
typedef struct process
{
	int id,totaltime;
	vector<t> tarr;
}p;
bool sortsjf(p p1,p p2)
{
	return p1.totaltime<p2.totaltime;
};
bool sortljf(p p1,p p2)
{
	return p1.totaltime>p2.totaltime;
};
p getp()
{
	int instances;
	p input;
	cout<<"Enter process ID: ";
	cin>>input.id;
	input.totaltime=0;
	cout<<"Give number of instances: ";
	cin>>instances;
	for (int i=0;i<instances;i++)
	{
		t inputt;
		cout<<"Give input for mode: ";
		cin>>inputt.mode;
		cout<<"Give input for time: ";
		cin>>inputt.time;
		input.totaltime=input.totaltime+inputt.time;
		input.tarr.push_back(inputt);
	}		
	return input;
};
void print(p p1)
{
	cout<<"p1.id = "<<p1.id<<endl;
	cout<<"p1.totaltime = "<<p1.totaltime<<endl;	
	cout<<"p1.mode = "<<p1.tarr[0].mode<<endl;
	cout<<"p1.time = "<<p1.tarr[0].time<<endl;
};
int calruntime(vector<p> v)
{
	int s=0;
	for (int i=0;i<v.size();i++)
	{
		for (int j=0;j<v[i].tarr.size();j++)
		{
		if (v[i].tarr[j].mode==1)
		{s=s+v[i].tarr[j].time;}
		}
	}
	return s;
};
int calwaittime(vector<p> v)
{
	int s=0;
	for (int i=0;i<v.size();i++)
	{
		for (int j=0;j<v[i].tarr.size();j++)
		{
		if (v[i].tarr[j].mode==2)
		{s=s+v[i].tarr[j].time;}
		}
	}
	return s;
};
int status;
int run(p &cpu,int runt)
{
	if (cpu.tarr[0].mode==2)
	{
		status=1;
		return 0;	
	}	
	else if (cpu.tarr.size()==1)
	{
		status=2;
		int time1=cpu.tarr[0].time;
		cpu.totaltime=0;
		cpu.tarr.erase(cpu.tarr.begin());
		return time1;
		//return runt;
	}
	else
	{
		status=3;		
		int time1=cpu.tarr[0].time;
		cpu.totaltime=cpu.totaltime-cpu.tarr[0].time;
		cpu.tarr.erase(cpu.tarr.begin());
		return time1;
	}
};
int runwaitqueue(vector<p> v,int time1)
{
	if (time1==0 || v[0].tarr[0].time>time1 || v.size()==0)
	{
		return -1;
	}
	int s=0,j;
	for (int i=0;i<v.size();i++)
	{
		j=i;
		if (s<=time1)
		{
			s=v[i].tarr[0].time+s;
		}	
		else
		{
			j=i;
			break;
		}
	}	
	return j;
};
int main()
{
	int e=1;
	int n1,n2;
	vector<p> b1,b2,wait;
	cout<<"Enter number of processes for first queue: ";
	cin>>n1;
	for (int i=0;i<n1;i++)
	{
		p input=getp();
		b1.push_back(input);	
		cout<<endl;	
	}
	cout<<"Enter number of processes for second queue: ";
	cin>>n2;
	for (int i=0;i<n2;i++)
	{
		p input=getp();
		b2.push_back(input);	
		cout<<endl;	
	}
	int runt=0,waitt=0;
	//cout<<"Successful input";	
	runt=calruntime(b1)+calruntime(b2);	
	waitt=calwaittime(b1)+calwaittime(b2);
	cout<<runt<<" "<<waitt<<endl;		
	while (runt>0)
	{
		sort(b1.begin(),b1.end(),sortsjf);
		sort(b2.begin(),b2.end(),sortljf);			
		p cpu;
		cpu=b1[0];
		cout<<"cpu = ";
		print(cpu);
		b1.erase(b1.begin());
		if (b2.size()!=0)
		{
			b1.push_back(b2[0]);
			b2.erase(b2.begin());
		}
		int runtime_exec=run(cpu,runt);
		runt=runt-runtime_exec;
		if (status!=2)
		{
			int no_of_p_wait=runwaitqueue(wait,runtime_exec);
			cout<<"no_of_p_wait = "<<no_of_p_wait<<endl;
			if (no_of_p_wait>=0)
			{
				//int no=min((int)wait.size()-1,no_of_p_wait);
				for (int i=0;i<=no_of_p_wait;i++)
				{
					waitt=waitt-wait[i].tarr[0].time;
					cout<<"Process(es) that ran in waiting queue during this time slice - "<<endl;
					print(wait[i]);
					wait[i].totaltime=wait[i].totaltime-wait[i].tarr[0].time;
					if (wait[i].tarr.size()>1)
					{
						p push=wait[i];
						push.tarr.erase(push.tarr.begin());
						b2.push_back(push);
					}
				}
				wait.erase(wait.begin(),wait.begin()+no_of_p_wait+1);
			}
		}
		if (status==1)
		{
			cout<<"Process in cpu shifted to waiting queue directly"<<endl;
			p cpucopy=cpu;
			wait.push_back(cpucopy);
		}
		else if (status==2)
		{
			cout<<"Process in cpu terminated"<<endl;			
		}
		else
		{
			cout<<"Process in cpu shifted to waiting queue after running in cpu"<<endl;
			p cpucopy=cpu;
			wait.push_back(cpucopy);
		}	
		cout<<"Total computation running time remaining = "<<runt<<endl;
	//	cout<<"Total input/output time remaining = "<<waitt<<endl;
		cout<<"----------------------------------------------------------"<<endl;	
	}
	if (waitt>0)
	{
		cout<<"Process(es) run after computation time for process(es) in CPU is over - "<<endl;
		for (int i=0;i<wait.size();i++)
		{
			print(wait[i]);
		}
	}
	return 0;
}
