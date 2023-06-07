graph={
    'Q1':[(6,1)],
    'Q2':[(1,2)],
    'Q3':[(5,3)],
    'Q4':[(7,4)],
    'Q5':[(4,5)],
    'Q6':[(3,6)],
    'Q7':[(8,7)],
    'Q8':[(1,8)]
}
queens=['Q1','Q2','Q3','Q4','Q5','Q6','Q7','Q8']

def cheack(row,column):
    
    for queen in queens:
        
        for xrow,xcolumn in graph[queen]:
            if(row==xrow and column==xcolumn):
                return 1;
    return 0;

def attacking_queen():
    cnt =0;
    for j in range(8):
        for row,column in graph[queens[j]]:
        
            new_row=row
            new_col=column

            # In a same row
            for i in range(8):

                new_col=new_col+1;
                if(new_row<=8):
                    cnt=cnt+cheack(new_row,new_col)

            new_row=row
            new_col=column
            #Diagonally up        
            for i in range(8):
                new_row=new_row+1;
                new_col=new_col+1;
                if new_row<=8 and new_col<=8:
                    cnt=cnt+cheack(new_row,new_col)
            #Diagonally Down
            new_row=row
            new_col=column
            for i in range(8):
                new_row=new_row-1;
                new_col=new_col+1;
                if new_row>=1 and new_col>=1:
                    cnt=cnt+cheack(new_row,new_col)
            #print(queens[j]," ",cnt);
    return cnt;

print("Attacking pairs: ",attacking_queen())





