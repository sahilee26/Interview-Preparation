int Solution::climbStairs(int A) {
    if(A==0 || A==1)
        return 1;
    return climbStairs(A-1)+climbStairs(A-2);
}
