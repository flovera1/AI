#include <iostream>

using namespace std;
/**
* funny way to double the number and add 1 
* doing shift to the left!(<<)
*/
int Left(int iIndex){
	return ((iIndex << 1) + 1);
}
int Right(int iIndex){
	return ((iIndex << 1) + 2);
}
int Parent(int iIndex){
	return ((iIndex - 1) >> 1);
}
void Swap(int& irX, int& irY){
	int temp = irX;
	irX       = irY;
	irY       = temp;

}
int main(){
}