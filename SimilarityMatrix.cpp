#include <vector>
#include <algorithm>

using namespace std;

class SimilarityMatrix{
	private:
		int similarityThreshold,documentCount;
		vector<vector<int>*> matrix;
		// TODO replace the vector with simple list

	public:
		SimilarityMatrix(int docCount,int similarityThreshold = 10){
			this->similarityThreshold = similarityThreshold;
			documentCount = docCount;
			for(int i=1;i<documentCount;i++){
				matrix.push_back(new vector<int>);
				for(int j=0;j<i;j++){
					matrix.at(i-1)->push_back(0);
				}
			}
		}

		~SimilarityMatrix(){
			for(int i=0;i<matrix.size();i++){
				delete matrix.at(i);
			}
		}

		void insertOccurance(int firstDocId,int secondDocId){
			int origin = firstDocId<secondDocId?secondDocId:firstDocId;
			origin--;   // This is because the matrix neglects the first document
			int index = firstDocId>secondDocId?secondDocId:firstDocId;

			matrix.at(origin)->at(index)++;
		}

		vector<int>* getSimilarity(int docId){
			vector<int>* resultList = new vector<int>;
			for(int i=0;i<matrix.size();i++){
				if(matrix.at(i)->size() > docId){
					if(matrix.at(i)->at(docId) >= similarityThreshold){
						resultList->push_back(i+1);
					}
				}
			}
			if(docId > 0){
				for(int i=0;i<matrix.at(docId-1)->size();i++){
					if(matrix.at(docId-1)->at(i) >= similarityThreshold){
						resultList->push_back(matrix.at(docId-1)->at(i));
					}
				}
			}
			std::sort(resultList->begin(),resultList->end());
			return resultList;
		}
};
