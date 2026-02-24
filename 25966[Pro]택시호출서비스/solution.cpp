#include<vector>
#include<set>
using namespace std;

struct Result
{
	int mX, mY;
	int mMoveDistance;
	int mRideDistance;
};

struct Taxi {
	int mX, mY;
	int mMoveDistance;
	int mRideDistance;
};

vector<Taxi> T;
set<pair<int, int>> RideDistance; // will sort based on -distance, taxinum

int MaxTaxi;
int MaxDist;

int dist(int sX, int sY, int dX, int dY){
	int absX, absY;
	if((sX-dX)<0){
		absX = -(sX-dX);
	}else{
		absX = sX-dX;
	}
		if((sY-dY)<0){
		absY = -(sY-dY);
	}else{
		absY = sY-dY;
	}
	return absY + absX;
}

void init(int N, int M, int L, int mXs[], int mYs[])
{
	T.clear();
RideDistance.clear();
	MaxDist = L;
	T.resize(M+1);
	MaxTaxi = M;
	for(int i =1;i<=M;i++){
		T[i].mX = mXs[i-1];
		T[i].mY = mYs[i-1];
		T[i].mMoveDistance = 0;
		T[i].mRideDistance = 0;
		RideDistance.insert({0,i}); //initialize to 0
	}
	return;
}	

int pickup(int mSX, int mSY, int mEX, int mEY)
{
	int min = 10000000;
	vector<pair<int,int>> goodTaxis; // save pair of <taxinum, distance>
	for(int i = 1; i<=MaxTaxi;i++){ // for all taxis, calculate distance. save minimum, and if the minimum changes or is equal to minimum, save it to goodTaxis
		int temp = dist(mSX, mSY, T[i].mX, T[i].mY);
		if(temp <= min){
			min = temp;
			goodTaxis.push_back({i,temp});}
		}
	if(min>MaxDist){return -1;} // if min > L
	auto it = goodTaxis.begin();
	for(int i = 0 ; i<goodTaxis.size();i++){
		if(min==it->second){//if at taxi is in goodtaxis with equal distance to them minimum
			int j = it->first;
			RideDistance.erase({-T[j].mRideDistance,j}); // delete the original
			T[j].mMoveDistance += dist(mSX, mSY, T[j].mX, T[j].mY) + dist(mSX, mSY, mEX, mEY);
			T[j].mRideDistance += dist(mSX, mSY, mEX, mEY);
			RideDistance.insert({-T[j].mRideDistance,j}); // insert new -> O(log n) per pickup()
			T[j].mX= mEX;
			T[j].mY = mEY;
			return j;
		
		}it++;
	}
	return -1;

}

Result reset(int mNo)
{
	Result res;
	res.mX = T[mNo].mX;
	res.mY = T[mNo].mY;
	res.mMoveDistance = T[mNo].mMoveDistance;
	res.mRideDistance = T[mNo].mRideDistance;
	RideDistance.erase({-T[mNo].mRideDistance,mNo});
	RideDistance.insert({0,mNo});// erase and insert new entry
	T[mNo].mMoveDistance = T[mNo].mRideDistance = 0;
	
	return res;
}

void getBest(int mNos[])
{
//insert -distance, taxi num i pairs into set(so the biggest come first)
	auto it = RideDistance.begin();
	for(int i=0;i<5;i++){
		mNos[i] = it->second;
		it++;
	}
	
	return;
}