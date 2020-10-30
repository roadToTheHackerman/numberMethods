#include <bits/stdc++.h>
#define e 0.0001
using  namespace std;
int n;
double** baseMatrix;
double** oneMatrix;
double** inversedMatrix;
double** tempMatrix;
double* line;
void enter(istream& in,int mode){
    in>>n;
    baseMatrix = new double* [n+1];
    oneMatrix = new double* [n+1];
    inversedMatrix = new double* [n+1];
    tempMatrix = new double* [n+1];
    for(int i = 1;i<=n;i++){
        baseMatrix[i] = new double [n+1];
        oneMatrix[i] = new double [n+1];
        inversedMatrix[i] = new double [n+1];
        tempMatrix[i] = new double [n+1];
        fill(oneMatrix[i],oneMatrix[i]+n+1,0);
        oneMatrix[i][i] = 1;
    }
    ofstream oFile("out.txt");
    if(mode==1)oFile<<n<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mode==1){
                baseMatrix[i][j] = rand()%20;
                oFile<<baseMatrix[i][j]<<' ';
            }
            else
                in>>baseMatrix[i][j];
        }

        if(mode==1)oFile<<endl;
    }
}

double* inverse(){
    double m[n+1][n+1];
    double* x = new double [n+1];
    int max;
    double* ta;
    double tb;
    for(int k=1;k<=n;k+=1){
        max = k;
        for(int i=k+1;i<=n;i++){
            if(abs(tempMatrix[i][k])>abs(tempMatrix[max][k]))max = i;
        }
        swap(tempMatrix[k],tempMatrix[max]);
        swap(line[max],line[k]);
        if(abs(tempMatrix[k][k])<e){
            cout<<"There isn't inverted matrix\n";
            exit(0);
        }
        for(int i=k+1;i<=n;i++){
            m[i][k] = -(tempMatrix[i][k]/tempMatrix[k][k]);
            line[i] = line[i]+line[k]*m[i][k];
            for(int j=k+1;j<=n;j++)
                tempMatrix[i][j] = tempMatrix[i][j]+m[i][k]*tempMatrix[k][j];
        }
    }
    x[n] = line[n]/tempMatrix[n][n];
    double sum;
    for(int i=n-1;i>0;i--){
        for(int j=i+1;j<=n;j+=1){
            sum+=tempMatrix[i][j]*x[j];
        }
        x[i] = (line[i]-sum)/tempMatrix[i][i];
        sum = 0;
    }
    return x;
}

int main(){
    int cmd;
    cout<<"Enter 1 if you want to gen matrix,enter 2 if you want to work with file\n";
    cin>>cmd;
    if(cmd==1){cout<<"Enter size of matrix\n";enter(cin,1);}
    else{
        cout<<"Enter filepath\n";
        char path[256];
        cin>>path;
        ifstream inFile(path);
        enter(inFile,2);
    }
    for(int i=1;i<=n;i++){
        line = oneMatrix[i];
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                tempMatrix[j][k] = baseMatrix[j][k];
            }
        }
        inversedMatrix[i] = inverse();
    }
    cout<<"Inverted matrix\n";
    ofstream out("out.txt");
    for(int i = 1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<inversedMatrix[j][i]<<' ';
        cout<<endl;
    }
}