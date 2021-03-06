class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        // DFS: Time~O(N!), Space~O(N)
        vector<vector<int> > res;
        perm(num, 0, num.size()-1, res);
        return res;
    }
    
    void perm(vector<int> num, int l, int r, vector<vector<int> >& res) {
        if(l == r) {
            res.push_back(num);
            return;
        }
        
        for ( int i = l; i <= r; i++) {
            // swap i and l;
            int tmp = num[i];
            num[i] = num[l];
            num[l] = tmp;
            
            perm(num, l+1, r, res);
            
            // swap back
            tmp = num[i];
            num[i] = num[l];
            num[l] = tmp;
            
        }
    }
};