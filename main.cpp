#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
class matrix
{
private:
    int n_r,n_c;//矩阵行数、列数
    double data[50][50];//矩阵大小上限为50x50
    char name[10];
public:
    int get_n_r(){return n_r;}//返回行数
    int get_n_c(){return n_c;}//返回列数
    double get_data(int i,int j){return data[i][j];}//返回某元素
    void init(int ,int,char[]);//初始化矩阵
    void cin_data();//手动输入矩阵数据
    void show_mat();//打印矩阵
    void edit_data(double new_data[50][50]);//使用二维数组改变矩阵值
    double* get_row(int);//返回矩阵某一行
    double* get_col(int);//返回矩阵某一列
    char* show_name(){return name;}//返回矩阵名称
};
void matrix::init(int a,int b,char s[])
{
    n_r=a;
    n_c=b;
    strcpy(name,s);
}
void matrix::cin_data()
{   
    cout<<"请按行输入矩阵内容("<<n_r<<"x"<<n_c<<")："<<endl;
    for(int k=0;k<n_r;k++)
    {   
        cout<<"请输入第"<<k+1<<"行"<<endl;
        int i=0;
        if(k==0)getchar();
        char temp[500],*p=temp;
        cin.getline(temp, 500);
        bool negitive=false;
        while(i<n_c)
        {
            if(*p=='-')
            {
                p++;
                negitive=true;
            }
            double t=0;
            while((*p!=' ')&&(*p!='\0'))
                {
                    t=10*t+double(*p-48);
                    p++;
                }
            if(negitive)t=-t;
            data[k][i]=t;
            negitive=false;
            if((*p)=='\0')break;
            p++;
            i++;        
        }
    }cout<<"已生成";
    show_mat();
}
void matrix::show_mat()
{
    int lenth=12;
    cout<<"矩阵名: "<<name<<"  矩阵大小: "<<n_r<<'x'<<n_c<<endl;
    for(int i=0;i<n_r;i++)
    {
        cout<<'[';
        for(int j=0;j<n_c;j++)
        {
            if(data[i][j]<1e-16&&data[i][j]>-1e-16)cout<<setw(lenth-1)<<0.0;
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
double vector_dot(double*a,double*b,int n)//向量点积
{
    double result=0;
    for(int i=0;i<n;i++)
    {
        result+=a[i]*b[i];
    }
    return result;
}
void num_multiply_menu(matrix mats[],int &n)
{
    char mat1[10],name[10];
    double k;
    int a=-1,b=-1;
    cout<<"输入要做数乘的矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        cout<<"输入要做乘法的数字:"<<endl;
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
        cout<<"已完成运算"<<endl;
        mats[a].show_mat();
    }
    system("read -p \"回车以继续\"");
    return;
}
matrix multiply_method(matrix A,matrix B,char*s)//矩阵乘法
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
void multiply_menu(matrix mats[],int &n)
{
    char mat1[10],mat2[10],name[10];
    int a=-1,b=-1;
    cout<<"输入要做乘法的第一个矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        cout<<"输入要做乘法的第二个矩阵（输入名字）:"<<endl;
        cin>>mat2;
        for(int i=0;i<n;i++)
        {
            if(strcmp(mats[i].show_name(),mat2)==0)b=i;
        }
        if(b==-1)
        {
            cout<<"找不到相应的矩阵"<<endl;
        }
        else
        {
            mats[b].show_mat();
            if(mats[a].get_n_c()!=mats[b].get_n_r())
            {
                cout<<"两矩阵不能相乘("<<mats[a].get_n_c()<<"!="<<mats[b].get_n_r()<<")"<<endl;
            }
            else
            {
                cout<<"请输入相乘矩阵的名字:"<<endl;
                cin>>name;
                mats[n]=multiply_method(mats[a],mats[b],name);
                n++;
                cout<<"已完成运算"<<endl;
                mats[n-1].show_mat();
            }
        }
    }
    system("read -p \"回车以继续\"");
    return;
}
matrix plus_method(matrix A,matrix B,char*s)//矩阵加法
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
void plus_menu(matrix mats[],int &n)
{
    char mat1[10],mat2[10],name[10];
    int a=-1,b=-1;
    cout<<"输入要做加法的第一个矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        cout<<"输入要做加法的第二个矩阵（输入名字）:"<<endl;
        cin>>mat2;
        for(int i=0;i<n;i++)
        {
            if(strcmp(mats[i].show_name(),mat2)==0)b=i;
        }
        if(b==-1)
        {
            cout<<"找不到相应的矩阵"<<endl;
        }
        else
        {
            mats[b].show_mat();
            if(mats[a].get_n_r()!=mats[b].get_n_r()||mats[a].get_n_c()!=mats[b].get_n_c())
            {
                cout<<"两矩阵不能相加！"<<endl;
            }
            else
            {
                cout<<"请输入相加矩阵的名字:"<<endl;
                cin>>name;
                mats[n]=plus_method(mats[a],mats[b],name);
                n++;
                cout<<"已完成运算"<<endl;
                mats[n-1].show_mat();
            }
        }
    }
    system("read -p \"回车以继续\"");
    return;
}
matrix power_method(matrix A,char name[10],int power)
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
void power_menu(matrix mats[],int &n)
{
    char mat1[10],name[10];
    int a=-1,power;
    cout<<"输入要做幂次计算的矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        if(mats[a].get_n_r()!=mats[a].get_n_c())
        {
            cout<<"该矩阵不是方阵！"<<endl;
        }
        else
        {
            cout<<"输入指数:"<<endl;
            cin>>power;
            cout<<"请输入幂次计算后矩阵的名字:"<<endl;
            cin>>name;
            mats[n]=power_method(mats[a],name,power);
            n++;
            cout<<"已完成运算"<<endl;
            mats[n-1].show_mat();
        }
    }
    system("read -p \"回车以继续\"");
    return;
}
double str_to_double(char *t)
{
    double k=0,result=0;
    char *p=t;
    bool doted=false,negitive=false,_e=false,_e_sign=true;
    //check inf or nan
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
matrix* load_data(matrix mats[],int&n)
{
    ifstream infile;
    infile.open("/Users/lulu/Desktop/C++/Matrix_cal/Matrix_calculator/data.txt",ios::in);
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
void input(matrix mats[],int &n)
{
    while(true)
    {
        char name[10],sure;
        int m1,m2;
        cout<<"现定义新矩阵。请输入矩阵名字(输入0退出)："<<endl;
        cin>>name;
        if(name[0]=='0')break;
        cout<<"请输入矩阵行数："<<endl;
        cin>>m1;
        cout<<"请输入矩阵列数："<<endl;
        cin>>m2;
        matrix new_mat;
        new_mat.init(m1,m2,name);
        new_mat.cin_data();
        cout<<"你确定要保存这个矩阵吗？(y/n)"<<endl;
        cin>>sure;
        if(sure=='Y'||sure=='y')
        {
            mats[n]=new_mat;
            n+=1;
        }
    }
    cout<<"已保存矩阵数据"<<endl;
    system("read -p \"按回车键继续\"");
    return;
}
void output(matrix mats[],int n)
{
    cout<<"显示已有矩阵："<<endl;
    if(n==0)cout<<"暂未定义任何矩阵"<<endl;
    for(int i=0;i<n;i++)
    {
        mats[i].show_mat();
        cout<<endl;
    }
    system("read -p \"回车键继续\"");
}
void save_data(matrix* mats,int n)
{
    ofstream outfile;
    outfile.open("/Users/lulu/Desktop/C++/Matrix_cal/Matrix_calculator/data.txt",ios::out);
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
                if(mats[i].get_data(j1,j2)<1e-16&&mats[i].get_data(j1,j2)>-1e-16)outfile<<0;
                else outfile<<mats[i].get_data(j1,j2);
                if(j2<mats[i].get_n_c()-1)outfile<<' ';
            }
        }
        if(i<n-1)outfile<<endl;
    }
    cout<<"文件已保存 "<<endl;
    outfile.close();
    return;
}
double laplace_expansion(int n,double data[50][50])//拉普拉斯展开
{
    double sum=0;
    if(n==1)return data[0][0];
    if(n==2){
        return data[0][0]*data[1][1]-data[0][1]*data[1][0];
    }
    if(n>2)
    {
        double k=1;
        for(int i=0;i<n;i++)//按第一行展开
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
double determinant(matrix A)//计算行列式
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
void determinant_menu(matrix* mats,int n)
{
    cout<<"行列式计算:请输入方阵名称"<<endl;
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
            cout<<"该矩阵不是方阵"<<endl;
        }
        else
        {
            mats[chosen].show_mat();
            cout<<"其行列式的值为："<<determinant(mats[chosen])<<endl;
        }
    }
    else
    {
        cout<<"找不到该矩阵"<<endl;
    }
    system("read -p \"按回车键继续\"");
    return;
}
matrix transpose_method(matrix A)
{
    double new_data[50][50];
    matrix newmat;
    newmat.init(A.get_n_c(),A.get_n_r(),A.show_name());
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
void transpose_menu(matrix mats[],int n)
{
    char mat1[10],name[10];
    int a=-1,b=-1;
    cout<<"输入要转置的矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        mats[a]=transpose_method(mats[a]);
        cout<<"转置已完成"<<endl;
        mats[a].show_mat();
    }
    system("read -p \"回车以继续\"");
    return;
}
void swap_row(double data[50][50],int i,int j)
{
    double t;
    for(int k=0;k<50;k++)
    {
        t=data[i][k];
        data[i][k]=data[j][k];
        data[j][k]=t;
    }
}
void cancel_row(double data[50][50],int i,int j,int n_c,double k)//cancel的两行号&所在列
{   
    
    for(int l=0;l<50;l++)
    {
        data[j][l]=data[j][l]+k*data[i][l];
    }
}
void row_echelon_form(double data[50][50],int m,int n)//化为阶梯型
{
    int done_row=0;
    for(int i=0;i<n;i++)
    {
        if(data[done_row][i]==0)//首项不为0
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

int rank_method(matrix A,bool show_ladder=false)
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
        cout<<"矩阵的阶梯型为："<<endl;
        matrix t;
        char name[10]="阶梯型";
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
void rank_menu(matrix mats[],int n)
{
    char mat1[10],name[10];
    int a=-1,b=-1;
    cout<<"输入要计算秩的矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        int rank=rank_method(mats[a],true);
        cout<<"矩阵的秩为："<<rank<<endl;
    }
    system("read -p \"回车以继续\"");
    return;
}
void inverse(double data[50][50],int m,int n)//高斯消元法
{
    double inv[50][50];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            inv[i][j]=0;
            if(i==j)inv[i][j]=1;

        }
    }
    int done_row=0;
    for(int i=0;i<n;i++)
    {
        if(data[done_row][i]==0)//首项不为0
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
    //化为单位阵
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
}

void inverse_menu(matrix mats[],int &n)
{
    char mat1[10],name[10];
    int a=-1,b=-1;
    cout<<"输入要求逆的矩阵（输入名字）:"<<endl;
    cin>>mat1;
    for(int i=0;i<n;i++)
    {
        if(strcmp(mats[i].show_name(),mat1)==0)a=i;
    }
    if(a==-1)
    {
        cout<<"找不到相应的矩阵"<<endl;
    }
    else if(mats[a].get_n_r()!=mats[a].get_n_c()||(rank_method(mats[a])!=mats[a].get_n_r()))
    {
        mats[a].show_mat();
        cout<<"矩阵非方阵或不可逆"<<endl;
    }
    else 
    {
        mats[a].show_mat();
        matrix inv;
        char name[10];
        double copy_data[50][50];
        for(int i=0;i<50;i++)
        {
            for(int j=0;j<50;j++)
            {
                copy_data[i][j]=mats[a].get_data(i,j);
            }
        }
        cout<<"请输入逆矩阵的名字："<<endl;
        cin>>name;
        inv.init(mats[a].get_n_r(),mats[a].get_n_c(),name);
        inverse(copy_data,mats[a].get_n_r(),mats[a].get_n_c());
        inv.edit_data(copy_data);
        cout<<"运算已完成，逆矩阵为："<<endl;
        inv.show_mat();
        mats[n]=inv;
        n++;
    }

    system("read -p \"回车以继续\"");
    return;
}
int main()
{
    matrix mats1[50];
    int n=0,chosen_num;
    matrix *mats=load_data(mats1,n);
    while(1)
    {
        system("reset");//reset为Linux下清屏命令
        cout<<"\t\t"<<"矩阵计算器";
        cout<<" (已存在"<<n<<"个矩阵)";
        cout<<endl;
        cout<<" _______________________________________________"<<endl;
        cout<<"|  请选择数字(1-11):                            |"<<endl;
        cout<<"|-----------------------------------------------|"<<endl;
        cout<<"|   1.定义新矩阵          |  2.显示已有矩阵     |"<<endl;
        cout<<"|   3.矩阵加法计算        |  4.矩阵数乘计算     |"<<endl;
        cout<<"|   5.矩阵乘法计算        |  6.矩阵幂次计算     |"<<endl;
        cout<<"|   7.计算行列式          |  8.求矩阵转置       |"<<endl;
        cout<<"|   9.求矩阵的阶梯型和秩  |  10.求矩阵的逆      |"<<endl;
        cout<<"|   11.保存&退出          |                     |"<<endl;
        cout<<" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<"你的选择:";
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
            cout<<"正在退出...";
            getchar();
            break;
        }
    }
    return 0;
}
