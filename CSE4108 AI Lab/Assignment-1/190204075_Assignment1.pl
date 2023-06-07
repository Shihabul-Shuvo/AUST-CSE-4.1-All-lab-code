% Facts about family relationships

parent('john', 'mary').
parent('john', 'peter').
parent('sue', 'mary').
parent('sue', 'peter').
parent('mary', 'tom').
parent('peter', 'lisa').
parent('peter', 'bob').
parent('john', 'tyler').
parent('sue', 'tyler').

male('john').
male('peter').
male('tom').
male('bob').
male('tyler').

female('sue').
female('mary').
female('lisa').

% Rules to define family relationships
sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.

brother(X, Y) :-
    sibling(X, Y),
    male(X).

sister(X, Y) :-
    sibling(X, Y),
    female(X).

uncle(X, Y) :-
    parent(Z, Y),
    brother(X, Z).

aunt(X, Y) :-
    parent(Z, Y),
    sister(X, Z).

grandparent(Z, X) :-
    parent(Y, X),
    parent(Z, Y).

findGrandparent :- write('Enter a name to find their grandparents: '),
	    read(X),
		grandparent(Gp, X),
		  write('Grandparent is: '), write(Gp), tab(5),
		    fail.
