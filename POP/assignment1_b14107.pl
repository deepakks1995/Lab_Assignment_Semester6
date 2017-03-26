#	Name : Deepak Sharma
#   Roll No: B14107


# Defining Relations

parent(X,Y) :- father(X, Y);mother(X, Y).

sister(X,Y) :- female(X), parent(Z, X), parent(Z, Y).

brother(X, Y) :- parent(Z, X), parent(Z, Y), male(X).

grandFather(X, Y) :- father(Z, Y), father(X, Z).

grandmother(X, Y) :- father(Z, Y), mother(X, Z).  
	
grandson(X, Y) :- father(Z, X), parent(Y, Z).

son(X, Y) :- father(Y, X), male(X).

uncle(X, Y)	:- father(Z, Y), brother(X, Z).

married(X, Y) :- parent(X, Z), parent(Y, Z), not(X = Y).

maternaluncle(X, Y) :- mother(Z,Y), brother(X,Z).

siblings(X, Y) :- parent(Z, Y), parent(Z, X), not(X = Y).	

ancestor(X, Y) :- parent(X,Y);parent(X, Z), ancestor(Z, Y).
	
nephew(X, Y) :- brother(Z, Y), father(Z, X).

wife(X, Y) :- married(X, Y), female(X).
	
husband(X, Y) :- married(X, Y), male(X).

motherinlaw(X, Y) :- married(Z, Y), mother(X, Z).

fatherinlaw(X, Y)  :- married(Z, Y), father(X, Z).

soninlaw(X, Y) :- married(Z, X), parent(Y, Z), male(X).

daughterinlaw(X, Y) :- married(Z, X), parent(Y,Z), female(X).

grandchild(X, Y) :- parent(Z, X), parent(Y,Z).

maternalgrandFather(X, Y) :- mother(Z, Y), father(X, Z).

maternalgrandmother(X, Y) :- mother(Z, Y), mother(X, Z).

aunt(X, Y) :- father(Z, Y), brother(Z, X).

brotherinlaw(X,Y) :- married(Z, Y), brother(X, Z).

sisterinlaw(X,Y) :- married(Z, Y), sister(X, Z).

cousin(X,Y) :- parent(Z1, Y), parent(Z2, X), siblings(Z1, Z2).

daughter(X, Y) :- parent(Y, X), female(X).

maternalaunt(X,Y):- sister(X,Z),mother(Z,Y).

niece(X, Y) :- siblings(Z, Y), parent(Z, X), female(X).


# Defining Facts
# Father(Father, Person)
father(ashish, anuj).
father(ashish, ashok).
father(ashish, sophia).
father(jackson, ashish).
father(lucas, neha).
father(anuj, logan).
father(jackson, mason).
father(lucas, caden).
father(jayden, jackson).
father(elijah, isabella).
father(jackson, madison).
father(elijah, jack).
father(elijah, charlotte).
father(mason, benjamin).
father(anuj, amelia).
father(lucas, scarlett).

# Mother(Mother, Person)
mother(mia, jackson).
mother(olivia, caden).
mother(emma, mason).
mother(isabella, logan).
mother(emma, ashish).
mother(olivia, neha).
mother(neha, sophia).
mother(neha, ashok).
mother(neha, anuj).
mother(zoe, isabella).
mother(emma, madison).
mother(zoe, jack).
mother(zoe, charlotte).
mother(isabella, amelia).
mother(olivia, scarlett).

# Male(Person)
male(ashish).
male(ashok).
male(jackson).
male(lucas).
male(anuj).
male(logan).
male(anuj).
male(mason).
male(caden).
male(jayden).
male(elijah).
male(jack).
male(benjamin).

# Female(Person)
female(sophia).
female(neha).
female(mia).
female(olivia).
female(emma).
female(isabella).
female(zoe).
female(madison).
female(charlotte).
female(amelia).
female(scarlett).