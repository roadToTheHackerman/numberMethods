#include <bits/stdc++.h>
#define e 0.0001
using  namespace std;
int n;
double** a;
double** l;
double** u;
double* b;
double* x;
double* y;

void enter(istream& in,int mode){
    in>>n;
    a = new double* [n+1];
    u = new double* [n+1];
    l = new double* [n+1];
    b = new double [n+1];
    for(int i = 1;i<=n;i++){
        a[i] = new double [n+1];
        u[i] = new double [n+1];
        l[i] = new double [n+1];
    }
    ofstream oFile("out.txt");
    if(mode==1)oFile<<n<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mode==1){
                u[i][j] = a[i][j] = rand()%200-100;
                oFile<<a[i][j]<<' ';
            }
            else{
                in>>a[i][j];
                u[i][j] = a[i][j];
            }

        }

        if(mode==1){b[i] = rand()%200-50;oFile<<b[i]<<endl;}
        else{
            in>>b[i];
        }
    }
}

int main(){
    int cmd;
    cout<<"Enter 1 if you want to gen equation,enter 2 if you want to work with file\n";
    cin>>cmd;
    if(cmd==1){cout<<"Enter size of the system\n";enter(cin,1);}
    else{
        cout<<"Enter filepath\n";
        char path[256];
        cin>>path;
        ifstream inFile(path);
        enter(inFile,2);
    }
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            l[j][i]=u[j][i]/u[i][i];

    for(int k = 2; k <= n; k++)
    {
        for(int i = k-1; i <= n; i++)
            for(int j = i; j <= n; j++)
                l[j][i]=u[j][i]/u[i][i];

        for(int i = k; i <= n; i++)
            for(int j = k-1; j <= n; j++)
                u[i][j]=u[i][j]-l[i][k-1]*u[k-1][j];
    }

    y = new double [n+1];
    y[0] = 0;
    double rez;
    for(int i=1;i<=n;i++){
        y[i] = b[i];
        for(int j=1;j<i;j++){
            y[i] = y[i]-l[i][j]*y[j];
        }
        y[i]/=l[i][i];
    }
    cout<<"\n----------------\n";
    cout<<"Y matrix\n";
    for(int i=1;i<=n;i++){
        cout<<y[i]<<' ';
    }
    x = new double [n+1];
    for(int i=n;i>=1;i--){
        x[i] = y[i];
        for(int j=n;j>i;j--){
            x[i] = x[i]-u[i][j]*x[j];
        }
        x[i]/=u[i][i];

    }
    cout<<"\n----------------\n";
    cout<<"X matrix\n";
    for(int i=1;i<=n;i++){
        cout<<x[i]<<' ';
    }
    cout<<"\n---------------------\n";
    cout<<"A matrix\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }
    cout<<"--------------------\n";
    cout<<"L matrix\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<l[i][j]<<' ';
        cout<<endl;
    }
    cout<<"-------------------\n";
    cout<<"U matrix\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<u[i][j]<<' ';
        cout<<endl;
    }
}
