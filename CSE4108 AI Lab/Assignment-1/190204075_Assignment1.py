while True:
    # Assignment01

    tupleList1 = [('parent', 'john', 'mary'),
                  ('parent', 'john', 'peter'),
                  ('parent', 'sue', 'mary'),
                  ('parent', 'sue', 'peter'),
                  ('parent', 'mary', 'tom'),
                  ('parent', 'peter', 'lisa'),
                  ('parent', 'peter', 'bob'),
                  ('parent', 'john', 'tyler'),
                  ('parent', 'sue', 'tyler')]
    
    genderList = [('male', 'john'),
                  ('male', 'peter'),
                  ('male', 'tom'),
                  ('male', 'bob'),
                  ('male', 'tyler'),
                  ('female', 'sue'),
                  ('female', 'mary'),
                  ('female', 'lisa')]

    ch = int(input("Enter your choice to find the relation of:\n1. Brother\n2. Sister\n3. Uncle\n4. Aunt\n5. Grandparents\nChoice: "))

    if ch == 1 or ch == 2:
        X = input("Enter the name to find the siblings: ")
        if ch == 1:
            print("Brother: ", end=' ')
        else:
            print("Sister: ", end=' ')
        
        for i in range(len(tupleList1)):
            if tupleList1[i][0] == 'parent' and tupleList1[i][2] == X:
                for j in range(len(tupleList1)):
                    if tupleList1[j][0] == 'parent' and tupleList1[i][1] == tupleList1[j][1] and tupleList1[j][2] != X:
                        for k in range(len(genderList)):
                            if ch == 1:
                                if genderList[k][0] == 'male' and genderList[k][1] == tupleList1[j][2]:
                                    print(tupleList1[j][2], end=' ')
                            else:
                                if genderList[k][0] == 'female' and genderList[k][1] == tupleList1[j][2]:
                                    print(tupleList1[j][2], end=' ')
        print()
        
    elif ch == 3 or ch == 4:
        X = input("Enter the name to find someone's uncle/aunt: ")
        if ch == 3:
            print("Uncle: ", end=' ')
        else:
            print("Aunt: ", end=' ')
        
        for l in range(len(tupleList1)):
            if tupleList1[l][0] == 'parent' and tupleList1[l][2] == X:
                for i in range(len(tupleList1)):
                    if tupleList1[i][0] == 'parent' and tupleList1[i][2] == tupleList1[l][1]:
                        for j in range(len(tupleList1)):
                            if tupleList1[j][0] == 'parent' and tupleList1[i][1] == tupleList1[j][1] and tupleList1[j][2] != tupleList1[l][1]:
                                for k in range(len(genderList)):
                                    if ch == 3:
                                        if genderList[k][0] == 'male' and genderList[k][1] == tupleList1[j][2]:
                                            print(tupleList1[j][2], end=' ')
                                    else:
                                        if genderList[k][0] == 'female' and genderList[k][1] == tupleList1[j][2]:
                                            print(tupleList1[j][2], end=' ')
        print()
        
    elif ch == 5:
        X = input("Enter the name to find someone's grandparent: ")
        print('Grandparent:', end=' ')
        
        for i in range(len(tupleList1)):
            if tupleList1[i][0] == 'parent' and tupleList1[i][2] == X:
                for j in range(len(tupleList1)):
                    if tupleList1[j][0] == 'parent' and tupleList1[i][1] == tupleList1[j][2]:
                        print(tupleList1[j][1], end=' ')
        print()
        
    else:
        print("Invalid choice. Please try again.")
