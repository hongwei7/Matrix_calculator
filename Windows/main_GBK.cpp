#include <cstdlib>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

double str_to_double(char *t)//��ֵ����
{
    double k=0,result=0;
    char *p=t;
    bool doted=false,negitive=false,_e=false,_e_sign=true;
    //���inf��nan
    switch(*p)
    {
        case('n'):return 0.0;
        case('i'):return 1.79769e+308;
    }
    if(*(p+1)=='i')
    {
        return -1.79769e+308;
    }
    while(true)
    {   
        if(_e)
        {
            int power=int(str_to_double(p));
            for(int i=0;i<power;i++)
            {
                if(_e_sign)result=result*10;
                else result=result/10;
            }
            break;
        }
        else
        {
            if(*(p)=='-'&&!_e)
            {
                negitive=true;
            }
            else if(*p=='e')
            {
                _e=true;
                p++;
                if(*p=='-')_e_sign=false;
                else if(*p!='+')continue;
            }
            else
            {
                if(*(p)!='\0')
                {
                    if(*(p)!='.')
                    {
                        if(!doted)result=result*10+int(*p-48);
                        if(doted){result=result+k*int(*p-48);k*=0.1;}
                    }
                    else
                    {
                        doted=true;
                        k=0.1;
                    }
                }
                else
                {
                    if(negitive)result=-result;
                    return result;
                }
            }
        }
        p++;
    }
    if(negitive)result=-result;
    return result;
}
//�����ඨ�岿��
class matrix
{
private:
    int n_r,n_c;//��������������
    double data[50][50];//�����С����Ϊ50x50
    char name[10];//������(���ھ������)
public:
    int get_n_r(){return n_r;}//��������
    int get_n_c(){return n_c;}//��������
    double get_data(int i,int j){return data[i][j];}//����ĳԪ��
    void init(int ,int,char[]);//��ʼ������
    void cin_data();//�ֶ������������
    void show_mat();//��ӡ����
    void edit_data(double new_data[50][50]);//ʹ�ö�ά����ı����ֵ
    double* get_row(int);//���ؾ���ĳһ��
    double* get_col(int);//���ؾ���ĳһ��
    char* show_name(){return name;}//���ؾ�������
};
void matrix::init(int a,int b,char s[])
{
    n_r=a;
    n_c=b;
    strcpy(name,s);
}
void matrix::cin_data()
{   
    cout<<"�밴�������������("<<n_r<<"x"<<n_c<<")��"<<endl;
    for(int k=0;k<n_r;k++)
    {   
        cout<<"�������"<<k+1<<"��"<<endl;
        int i=0;
        if(k==0)getchar();
        char temp[500],*p=temp;
        cin.getline(temp, 500);
        while(i<n_c)
        {
            char char_number[20];
            for(int j=0;(*p!=' '&&*p!='\0');j++)
            {
                char_number[j]=*p;
                char_number[j+1]='\0';
                p++;
            }
            p++;
            data[k][i]=str_to_double(char_number);
            i++;        
        }
    }cout<<"������";
    show_mat();
}
void matrix::show_mat()
{
    int lenth=12;
    cout<<"������: "<<name<<"  �����С: "<<n_r<<'x'<<n_c<<endl;
    for(int i=0;i<n_r;i++)
    {
        cout<<'[';
        for(int j=0;j<n_c;j++)
        {
            if(data[i][j]<1e-5&&data[i][j]>-1e-5)cout<<setw(lenth-1)<<0.0;
            else cout<<setw(lenth-1)<<data[i][j];
            cout<<',';
        }
        cout<<'\b'<<"]"<<endl;
    }
}
double* matrix::get_row(int index)
{
    static double row[50],*p=row;
    for(int i=0;i<n_c;i++)
    {
        row[i]=data[index][i];
    }
    return p;
}
double* matrix::get_col(int index)
{
    static double col[50],*p=col;
    for(int i=0;i<n_r;i++)
    {
        col[i]=data[i][index];
    }
    return p;
}
void matrix::edit_data(double(*new_data)[50])
{
    for(int i=0;i<50;i++)
    {
        for(int j=0;j<50;j++)
        {
            data[i][j]=new_data[i][j];
        }
    }
}

//������㷽��
double vector_dot(double*a,double*b,int n)//�������
{
    double result=0;
    for(int i=0;i<n;i++)
    {
        result+=a[i]*b[i];
    }
    return result;
}
matrix plus_method(matrix A,matrix B,char*s)//����ӷ�
{
    matrix result;
    double new_data[50][50];
    result.init(A.get_n_r(),B.get_n_c(),s);
    for(int i=0;i<A.get_n_r();i++)
    {
        for(int j=0;j<B.get_n_c();j++)
        {
            new_data[i][j]=A.get_data(i,j)+B.get_data(i,j);
        }
    }
    result.edit_data(new_data);
    return result;
}
matrix multiply_method(matrix A,matrix B,char*s)//����˷�
{
    matrix result;
    double new_data[50][50];
    result.init(A.get_n_r(),B.get_n_c(),s);
    for(int i=0;i<A.get_n_r();i++)
    {
        for(int j=0;j<B.get_n_c();j++)
        {
            new_data[i][j]=vector_dot(A.get_row(i),B.get_col(j),A.get_n_c());
        }
    }
    result.edit_data(new_data);
    return result;
}
matrix power_method(matrix A,char name[10],int power)//�ݴμ���
{
    matrix B,*p;
    B.init(A.get_n_r(),A.get_n_c(),name);
    double data[50][50];
    if(power==0)
    {
        for(int i=0;i<A.get_n_c();i++)
        {
            for(int j=0;j<A.get_n_c();j++)
            {
                if(i==j)data[i][j]=1;
                else data[i][j]=0;
            }
        }
    }
    else
    {
        for(int i=0;i<50;i++)
        {
            for(int j=0;j<50;j++)
            {
                data[i][j]=A.get_data(i,j);
            }
        }
        B.edit_data(data);
        p=&B;
        for(int i=0;i<power-1;i++)
        {
            *p=multiply_method(*p,A,name);
        }
    }
    return *p;
}
double laplace_expansion(int n,double data[50][50])//������˹չ��
{
    double sum=0;
    if(n==1)return data[0][0];
    if(n==2){
        return data[0][0]*data[1][1]-data[0][1]*data[1][0];
    }
    if(n>2)
    {
        double k=1;
        for(int i=0;i<n;i++)//����һ��չ��
        {
            double divided_data[50][50];
            for(int j1=0;j1<n;j1++)
            {   if(j1<i)
                {
                    for(int j2=1;j2<n;j2++)
                    {
                        divided_data[j2-1][j1]=data[j2][j1];
                    }
                }
                else if(j1>i)
                {
                    for(int j2=1;j2<n;j2++)
                    {
                        divided_data[j2-1][j1-1]=data[j2][j1];
                    }
                }
            }
            sum+=k*data[0][i]*laplace_expansion(n-1,divided_data);
            k=-1*k;
        }
    }return sum;
}
double determinant(matrix A)//��������ʽ
{
    double data[50][50];
    for(int i=0;i<A.get_n_r();i++)
    {
        for(int j=0;j<A.get_n_c();j++)
        {
            data[i][j]=A.get_data(i,j);
        }
    }
    return laplace_expansion(A.get_n_r(),data);
}
matrix transpose_method(matrix A,char name[10])//����ת��
{
    double new_data[50][50];
    matrix newmat;
    newmat.init(A.get_n_c(),A.get_n_r(),name);
    for(int i=0;i<A.get_n_r();i++)
    {
        for(int j=0;j<A.get_n_c();j++)
        {
            new_data[j][i]=A.get_data(i,j);
        }
    }
    newmat.edit_data(new_data);
    return newmat;
}
void swap_row(double data[50][50],int i,int j)//��������
{
    double t;
    for(int k=0;k<50;k++)
    {
        t=data[i][k];
        data[i][k]=data[j][k];
        data[j][k]=t;
    }
}
void cancel_row(double data[50][50],int i,int j,int n_c,double k)//cancel�����к�&������
{   
    for(int l=0;l<50;l++)
    {
        data[j][l]=data[j][l]+k*data[i][l];
    }
}
void row_echelon_form(double data[50][50],int m,int n)//��Ϊ������
{
    int done_row=0;
    for(int i=0;i<n;i++)
    {
        if(data[done_row][i]==0)//����Ϊ0 -> ��������
        {
            for(int k=i+1;k<m;k++)
            {
                if(data[k][i]!=0)
                {
                    swap_row(data,i,k);
                    break;
                }
            }
            if(data[done_row][i]==0)continue;
        }
        for(int j=done_row+1;j<m;j++)
        {
            double k=-data[j][i]/data[done_row][i];
            cancel_row(data,done_row,j,i,k);
        }
        done_row++;
    }
}
int rank_method(matrix A,bool show_ladder=false)//��������
{
    int rank=0;
    double new_data[50][50];
    for(int i=0;i<50;i++)
    {
        for(int j=0;j<50;j++)
        {
            new_data[i][j]=A.get_data(i,j);
        }
    }
    row_echelon_form(new_data,A.get_n_r(),A.get_n_c());
    if(show_ladder)
    {
        cout<<"����Ľ�����Ϊ��"<<endl;
        matrix t;
        char name[10]="������";
        t.init(A.get_n_r(),A.get_n_c(),name);
        t.edit_data(new_data);
        t.show_mat();
    }
    for(;rank<min(A.get_n_c(),A.get_n_r());rank++)
    {
        int is_zero=0;
        for(int k=0;k<A.get_n_c();k++)
        {
            if(new_data[rank][k]!=0)is_zero++;
        }
        if(is_zero==0)return rank;
    }
    return rank;
}
matrix inverse_method(matrix A,int m,char name[10])//��������
{
    double inv[50][50],data[50][50];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            data[i][j]=A.get_data(i,j);
            inv[i][j]=0;
            if(i==j)inv[i][j]=1;
        }
    }
    int done_row=0;
    for(int i=0;i<m;i++)
    {
        if(data[done_row][i]==0)//����Ϊ0
        {
            for(int k=i+1;k<m;k++)
            {
                if(data[k][i]!=0)
                {
                    swap_row(data,i,k);
                    swap_row(inv,i,k);
                    break;
                }
            }
            if(data[done_row][i]==0)continue;
        }
        for(int j=done_row+1;j<m;j++)
        {
            double k=-data[j][i]/data[done_row][i];
            cancel_row(data,done_row,j,i,k);
            cancel_row(inv,done_row,j,i,k);
        }
        done_row++;
    }
    //�����ͻ�Ϊ��λ��
    done_row=m-1;
    for(int i=m-1;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            double k=-data[j][i]/data[done_row][i];
            cancel_row(data,done_row,j,i,k);
            cancel_row(inv,done_row,j,i,k);
        }
        done_row--;
    }
    for(int i=0;i<m;i++)
        {
            for(int j=0;j<50;j++)
            {
                inv[i][j]=inv[i][j]/data[i][i];
            }
        }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<50;j++)
        {
            data[i][j]=inv[i][j];
        }
    }
    matrix inv_mat;
    inv_mat.init(m,m,name);
    inv_mat.edit_data(inv);
    return inv_mat;
}


//�˵���ʾ������ѡ�񡢼��������ж�
void plus_menu(matrix mats[],int &n)//�ӷ��˵�
{
    char mat1[10],mat2[10],name[10];
    int a=-1,b=-1;
    cout<<"����Ҫ���ӷ��ĵ�һ�������������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        cout<<"����Ҫ���ӷ��ĵڶ��������������֣�:"<<endl;
        cin>>mat2;
        for(int i=0;i<n;i++)
        {
            if(strcmp(mats[i].show_name(),mat2)==0)b=i;
        }
        if(b==-1)
        {
            cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
        }
        else
        {
            mats[b].show_mat();
            if(mats[a].get_n_r()!=mats[b].get_n_r()||mats[a].get_n_c()!=mats[b].get_n_c())
            {
                cout<<"����������ӣ�"<<endl;
            }
            else
            {
                cout<<"��������Ӿ��������:"<<endl;
                cin>>name;
                mats[n]=plus_method(mats[a],mats[b],name);
                n++;
                cout<<"���������"<<endl;
                mats[n-1].show_mat();
            }
        }
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void num_multiply_menu(matrix mats[],int &n)//���˲˵�
{
    char mat1[10],name[10];
    double k;
    int a=-1,b=-1;
    cout<<"����Ҫ�����˵ľ����������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        cout<<"����Ҫ���˷�������:"<<endl;
        cin>>k;
        double new_data[50][50];
        for(int i=0;i<50;i++)
        {
            for(int j=0;j<50;j++)
            {
                new_data[i][j]=k*mats[a].get_data(i,j);
            }
        }
        mats[a].edit_data(new_data);
        cout<<"���������"<<endl;
        mats[a].show_mat();
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void multiply_menu(matrix mats[],int &n)//�˷��˵�
{
    char mat1[10],mat2[10],name[10];
    int a=-1,b=-1;
    cout<<"����Ҫ���˷��ĵ�һ�������������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        cout<<"����Ҫ���˷��ĵڶ��������������֣�:"<<endl;
        cin>>mat2;
        for(int i=0;i<n;i++)
        {
            if(strcmp(mats[i].show_name(),mat2)==0)b=i;
        }
        if(b==-1)
        {
            cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
        }
        else
        {
            mats[b].show_mat();
            if(mats[a].get_n_c()!=mats[b].get_n_r())
            {
                cout<<"�����������("<<mats[a].get_n_c()<<"!="<<mats[b].get_n_r()<<")"<<endl;
            }
            else
            {
                cout<<"��������˾��������:"<<endl;
                cin>>name;
                mats[n]=multiply_method(mats[a],mats[b],name);
                n++;
                cout<<"���������"<<endl;
                mats[n-1].show_mat();
            }
        }
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void power_menu(matrix mats[],int &n)//�ݴβ˵�
{
    char mat1[10],name[10];
    int a=-1,power;
    cout<<"����Ҫ���ݴμ���ľ����������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        if(mats[a].get_n_r()!=mats[a].get_n_c())
        {
            cout<<"�þ����Ƿ���"<<endl;
        }
        else
        {
            cout<<"����ָ��:"<<endl;
            cin>>power;
            cout<<"�������ݴμ������������:"<<endl;
            cin>>name;
            mats[n]=power_method(mats[a],name,power);
            n++;
            cout<<"���������"<<endl;
            mats[n-1].show_mat();
        }
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void determinant_menu(matrix* mats,int n)//����ʽ�˵�
{
    cout<<"����ʽ����:�����뷽������"<<endl;
    int chosen=-1;
    char name[10];
    cin>>name;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),name)==0)chosen=i;
    }
    if(chosen!=-1)
    {
        if(mats[chosen].get_n_c()!=mats[chosen].get_n_r())
        {
            cout<<"�þ����Ƿ���"<<endl;
        }
        else
        {
            mats[chosen].show_mat();
            cout<<"������ʽ��ֵΪ��"<<determinant(mats[chosen])<<endl;
        }
    }
    else
    {
        cout<<"�Ҳ����þ���"<<endl;
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void transpose_menu(matrix mats[],int &n)//ת�ò˵�
{
    char mat1[10],name[10];
    int a=-1,b=-1;
    cout<<"����Ҫת�õľ����������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        char name[10];
        cout<<"������ת�ú�������֣�"<<endl;
        cin>>name;
        mats[n]=transpose_method(mats[a],name);
        cout<<"ת�������"<<endl;
        mats[n].show_mat();
        n++;
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void rank_menu(matrix mats[],int n)//���Ȳ˵�
{
    char mat1[10],name[10];
    int a=-1,b=-1;
    cout<<"����Ҫ�����Ⱥͽ����͵ľ����������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        int rank=rank_method(mats[a],true);
        cout<<"�������Ϊ��"<<rank<<endl;
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void inverse_menu(matrix mats[],int &n)//�������˵�
{
    char mat1[10],name[10];
    int a=-1,b=-1;
    cout<<"����Ҫ����ľ����������֣�:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"�Ҳ�����Ӧ�ľ���"<<endl;
    }
    else if(mats[a].get_n_r()!=mats[a].get_n_c()||(rank_method(mats[a])!=mats[a].get_n_r()))
    {
        mats[a].show_mat();
        cout<<"����Ƿ���򲻿���"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        matrix inv;
        char name[10];
        cout<<"���������������֣�"<<endl;
        cin>>name;
        mats[n]=inverse_method(mats[a],mats[a].get_n_r(),name);
        cout<<"��������ɣ������Ϊ��"<<endl;
        mats[n].show_mat();
        n++;
    }

    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}

//IO����
matrix* load_data(matrix mats[],int&n)
{
    ifstream infile;
    infile.open("data.txt",ios::in);
    if(infile)
        {
            int i=-1;
            while(!infile.eof()&&(++i<50))
            {
                char t[20];
                int m1,m2;
                infile>>t>>m1>>m2;
                matrix newmat;
                newmat.init(m1,m2,t);
                double data[50][50];
                for(int j1=0;j1<m1;j1++)
                {
                    for(int j2=0;j2<m2;j2++)
                    {
                        infile>>t;
                        data[j1][j2]=str_to_double(t);
                    }
                }
                newmat.edit_data(data);
                mats[i]=newmat;
                n++;
            }
        }
    infile.close();
    return mats;
}
void save_data(matrix* mats,int n)
{
    ofstream outfile;
    outfile.open("data.txt",ios::out);
    for(int i=0;i<n;i++)
    {
        if(i>=1)outfile<<endl;
        outfile<<mats[i].show_name()<<' ';
        outfile<<mats[i].get_n_r()<<' '<<mats[i].get_n_c();
        for(int j1=0;j1<mats[i].get_n_r();j1++)
        {
            for(int j2=0;j2<mats[i].get_n_c();j2++)
            {
                if(j2==0)outfile<<endl;
                if((mats[i].get_data(j1,j2)<1e-5)&&(mats[i].get_data(j1,j2)>-1e-5))outfile<<0;
                else outfile<<mats[i].get_data(j1,j2);
                if(j2<mats[i].get_n_c()-1)outfile<<' ';
            }
        }
        if(i<n-1)outfile<<endl;
    }
    cout<<"�ļ��ѱ��� "<<endl;
    outfile.close();
    return;
}
void input(matrix mats[],int &n)
{
    while(true)
    {
        char name[10],sure;
        int m1,m2,a=-1;
        cout<<"�ֶ����¾����������������(����0�˳�)��"<<endl;
        cin>>name;
        for(int i=0;i<n;i++)
        {
            if(strcmp(mats[i].show_name(),name)==0)a=i;
        }
        if(a!=-1)
        {
            cout<<"�������Ѵ���"<<endl;
        }
        else
        {
            if(name[0]=='0')break;
            cout<<"���������������"<<endl;
            cin>>m1;
            cout<<"���������������"<<endl;
            cin>>m2;
            matrix new_mat;
            new_mat.init(m1,m2,name);
            new_mat.cin_data();
            cout<<"��ȷ��Ҫ�������������(y/n)"<<endl;
            cin>>sure;
            if(sure=='Y'||sure=='y')
            {
                mats[n]=new_mat;
                n+=1;
            }
        }
    }
    cout<<"�ѱ����������"<<endl;
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
    return;
}
void output(matrix mats[],int n)
{
    cout<<"��ʾ���о���"<<endl;
    if(n==0)cout<<"��δ�����κξ���"<<endl;
    for(int i=0;i<n;i++)
    {
        mats[i].show_mat();
        cout<<endl;
    }
    cout<<"�س�������"<<endl;
    getchar();
    getchar();
}


int main()//���������
{
    matrix mats1[50];
    int n=0,chosen_num;
    matrix *mats=load_data(mats1,n);
    while(1)
    {
        system("cls");
        cout<<"\t\t"<<"���������";
        cout<<" (�Ѵ���"<<n<<"������)";
        cout<<endl;
        cout<<" _______________________________________________"<<endl;
        cout<<"|  ��ѡ������(1-11):                            |"<<endl;
        cout<<"|-----------------------------------------------|"<<endl;
        cout<<"|   1.�����¾���          |  2.��ʾ���о���     |"<<endl;
        cout<<"|   3.����ӷ�����        |  4.�������˼���     |"<<endl;
        cout<<"|   5.����˷�����        |  6.�����ݴμ���     |"<<endl;
        cout<<"|   7.��������ʽ          |  8.�����ת��       |"<<endl;
        cout<<"|   9.�����Ľ����ͺ���  |  10.��������      |"<<endl;
        cout<<"|   11.����&�˳�          |                     |"<<endl;
        cout<<" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<"���ѡ��:";
        cin>>chosen_num;
        switch(chosen_num)
        {
            case(1):{input(mats,n);break;}
            case(2):{output(mats,n);break;}
            case(3):{plus_menu(mats,n);break;}
            case(4):{num_multiply_menu(mats,n);break;}
            case(5):{multiply_menu(mats,n);break;}
            case(6):{power_menu(mats,n);break;}
            case(7):{determinant_menu(mats,n);break;}
            case(8):{transpose_menu(mats,n);break;}
            case(9):{rank_menu(mats,n);break;}
            case(10):{inverse_menu(mats,n);break;}
            default:break;
        }
        if(chosen_num==11)
        {
            save_data(mats,n);
            getchar();
            cout<<"�����˳�...";
            getchar();
            break;
        }
    }
    return 0;
}
