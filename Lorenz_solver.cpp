
#include <vector>
#include<iostream>
#include <fstream>
using namespace std;
struct Node{
    /*vector of derivatives*/
    vector <double> tab;
    Node(int len){
        tab.resize(len);
    }
    double evaluate(double t){
    /*evaluate taylor polynomian for variable t*/
        double sum = 0;
        for(int i=tab.size()-1;i>=1;i--){
            sum+= tab[i];
            sum = sum * (t/i);
        }
        return sum + tab[0];
    }
    void display(){
        for(int i=0;i<tab.size();i++)
            cout << tab[i]<<" ";
        cout<<endl;
    }


};
void write_point_to_file(ofstream& file,vector <double> point){

    file << point[0] <<" ";
    for(int i=1;i<point.size();i++)
        file << point[i] << " ";
    file<<endl;

}
double mult(Node a,Node b,int n){
    /*give n deravative for series a*b*/
    double sum = 0;
    for(int i=0;i<=n;i++)
        sum += a.tab[i] * b.tab[n-i];
    return sum;
}
double add(Node a, Node b ,int n){
    /*give n deravative for series a + b*/
    return a.tab[n] + b.tab[n];
}
void step_lorentz_metod(int n,double t,vector<double>& point){
    /*n number of cofficient that we use*/
    /*t step*/
    /*point is point th*/
    Node x(n);
    Node y(n);
    Node z(n);

    double a,b,c;
    a = 10;
    b = 28;
    c = 8./3.;
    x.tab[0] = point[0];
    y.tab[0] = point[1];
    z.tab[0] = point[2];
    for (int i=0;i<n-1;i++){
        x.tab[i+1] = a*(y.tab[i]-x.tab[i]);
        y.tab[i+1] = b*x.tab[i] - mult(x,z,i) - y.tab[i];
        z.tab[i+1] = mult(x,y,i) - c * z.tab[i];
        x.tab[i+1] = x.tab[i+1]/(i+1);
        y.tab[i+1] = y.tab[i+1]/(i+1);
        z.tab[i+1] = z.tab[i+1]/(i+1);

    }

    point[0] = x.evaluate(t);
    point[1] = y.evaluate(t);
    point[2] = z.evaluate(t);

}
void write_solution_to_file(vector<double> starting_point,int n,double t,int k,string file_name){
    /*n number of cofficient that we use*/
    /*t step step*/
    /*k number of point that we want to copute*/
    /*file_name is name of file in which we compute*/
    ofstream file;
    file.open(file_name);
    write_point_to_file(file,starting_point);
    for(int i=0;i<k;i++){
        step_lorentz_metod(n,t,starting_point);
        write_point_to_file(file,starting_point);

    }

}

int main(){
    Node x(10);
    vector<double> point({ 1., 1., 1.,});
    write_solution_to_file(point, 10,0.01,10000,"lorenz.txt");
}
