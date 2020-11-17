#include <bits/stdc++.h>
using namespace std;
double** a;
double* b;
int n;
double* current;
double* previous;
double* check;


bool matrixCheck(){
    double sum = 0;
    for(int i=1;i<=n;i++){
        sum = 0;
        for(int j=1;j<=n;j++)
        {
            if(i!=j)sum+=abs(a[i][j]);
        }
        if(abs(a[i][i])<sum)return false;
    }
    return true;
}

bool symmCheck(){
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            if(a[i][j]!=a[j][i])return false;
    }
    return true;
}

double euclede(){
    for(int i=1;i<=n;i++){
        check[i] = 0;
        for(int j=1;j<=n;j++){
            check[i]+=a[i][j]*current[j];
        }
    }
    double euclid = 0;
    for(int i=1;i<=n;i++){
        euclid+=pow(check[i]-b[i],2);
    }
    return sqrt(euclid);
}


int main(){
    double eps;
    string path;
    int mode;
    cout<<"Enter path to the file\n";
    cin>>path;
    ifstream in(path);
    ofstream out("out.txt");
    cout<<"Enter epsilon\n";
    cin>>eps;
    in>>n;
    a = new double* [n+1];
    b = new double [n+1];
    current = new double [n+1];
    previous = new double [n+1];
    check = new double [n+1];
    for(int i=1;i<=n;i++){
        a[i] = new double [n+1];
        for(int j=1;j<=n;j++)
            in>>a[i][j];
        in>>b[i];
    }
    if(!matrixCheck()){
        cout<<"This matrix hasn't diagonal domination or is unsymmetric!";
        return 0;
    }
    cout<<"Enter start solves\n";
    for(int i=1;i<=n;i++){
        cin>>previous[i];
    }
    int nint = 0;
    do{
        for(int i=1;i<=n;i++){
            current[i] = (1.0*b[i]/a[i][i]);
            for(int j=1;j<=n;j++){
                if(i!=j){
                    current[i] = current[i] - ((a[i][j] / a[i][i]) * previous[j]);
                    previous[i] = current[i];
                }
            }
        }
        nint+=1;
    }while(euclede()>eps);
    for(int i=1;i<=n;i++)
        out<<current[i]<<' ';
    cout<<"Euclid norm: "<<euclede()<<endl;
    cout<<"Number iterations: "<<nint;
}
