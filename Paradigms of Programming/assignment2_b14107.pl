/**
*	Name: Deepak Sharma
*	Roll No: B14107
*	Name: Kapardi Trivedi
*	Roll No: B14110
*	
*	The assignment comprises of two family trees, (both are represented by the comments at the start) 
*	which are not related to each other by any means.
*/

start:-
	read_line_to_codes(user_input, L),
	tokenize_atom(L,X),
	iterate(X).

printList([H|T]):-with_output_to(atom(Output), maplist(write, [H|T])),write(Output),nl.

insert_space([],[]).
insert_space([H|T],[H,' '|TC]):-insert_space(T,TC).

iterate([R,Mid,X|T]):- relationFacts(R),Mid=of,firstQuery([who,is,the,R,of,X], Output),insert_space(Output,FinalOutput), printList(FinalOutput).
iterate([R,Mid,X|T]):- relationFacts(R),Mid=is,firstQuery([whose,R,is,X], Output), insert_space(Output, FinalOutput),printList(FinalOutput).
iterate([R,Mid,X|T]):- relationFacts(R),Mid=between,firstQuery([whose,R,is,X], Output), insert_space(Output, FinalOutput),printList(FinalOutput).
iterate([R,Mid,X|T]):-	iterate([Mid,X|T]). 


firstQuery([who,is,the,R,of,X],[the,R,of,X,is,Y]) :- call(R,Y,X).
firstQuery([whose,R,is,X],[X,is,the,R,of,Y]) :- call(R,X,Y).

findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,1);relations(What, Name2, Name1,0,1).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,2);relations(What, Name2, Name1,0,2).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,3);relations(What, Name2, Name1,0,3).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,4);relations(What, Name2, Name1,0,4).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,5);relations(What, Name2, Name1,0,5).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,6);relations(What, Name2, Name1,0,6).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,7);relations(What, Name2, Name1,0,7).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,8);relations(What, Name2, Name1,0,8).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,9);relations(What, Name2, Name1,0,9).
findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,10);relations(What, Name2, Name1,0,10).
%findRelationship(What, Name1, Name2):-relations(What, Name1, Name2,0,21);relations(What, Name2, Name1,0,21).


relations(What, Name1, Name2,N,M):-
  relation_facts(Facts, Name1, _),
  relations1(Facts, [], Name2, What1,N,M),
  atomic_list_concat(What1, What).

relations1(Facts, Forbidden, Name2, What, N, M):-
  not(N=M),N1 is N+1,
  member(Relation, Facts),
  call(Relation),
  %writeq(Relation),nl,
  relations2(Relation, Forbidden, Name2, What, N1, M).

relations2(Relation, Forbidden, Right, [Left, ' ', is, ' ', Right, '''s ', Name], N, M):-
  Relation =.. [Name, Left, Right],
  Forbidden \= Right.
relations2(Relation, Forbidden, Name2, [Left, ' ', is, ' '| What], N, M):-
  Relation =.. [Name, Left, Right],
  relation_facts(Facts, Right, _),
  Forbidden\=Right,
  not(N=M),N1 is N+1,
  relations1(Facts, Left, Name2, [_,_,_,_, NRight|What1],N1, M),
  append([NRight|What1], ['''s ', Name], What).
  %writeq(N1).

relation_facts([father(X,Y), mother(X,Y),siblings(X,Y),husband(X,Y),wife(X,Y),son(X,Y),daughter(X,Y)], X, Y). 

parent(X,Y) :- father(X, Y);mother(X, Y).

sister(X,Y) :- female(X), parent(Z, X), parent(Z, Y), not(X=Y).

brother(X, Y) :- parent(Z, X), parent(Z, Y), male(X), not(X=Y).

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


% Defining Database
% father (Father, Person)
% First Family
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

% mother(Mother, Person)
% First Family
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

% Second Family
father(alan, john).
father(alan, tywin).
father(alan, cersie).
father(tyrion, alan).
father(stannis, arya).
father(john, charles).
father(tyrion, leo).
father(stannis, jordan).
father(xavier, tyrion).
father(xander, natalie).
father(tyrion, elizabeth).
father(xander, nolan).
father(xander, claire).
father(leo, christopher).
father(john, katherine).
father(stannis, jasmine).



% Second Family
mother(catelyn, tyrion).
mother(jean, jordan).
mother(sansa, leo).
mother(natalie, charles).
mother(sansa, alan).
mother(jean, arya).
mother(arya, cersie).
mother(arya, tywin).
mother(arya, john).
mother(victoria, natalie).
mother(sansa, elizabeth).
mother(victoria, nolan).
mother(victoria, claire).
mother(natalie, katherine).
mother(jean, jasmine).

% male(Person)
% First Family
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

% Second Family
male(alan).
male(tywin).
male(tyrion).
male(stannis).
male(john).
male(charles).
male(leo).
male(jordan).
male(xavier).
male(xander).
male(nolan).
male(christopher).

% female(Person)
% First Family
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

% Second Family
female(cersie).
female(arya).
female(catelyn).
female(jean).
female(sansa).
female(natalie).
female(victoria).
female(elizabeth).
female(claire).
female(katherine).
female(jasmine).



relationFacts(parent).
relationFacts(father).
relationFacts(mother).
relationFacts(sister).
relationFacts(brother).
relationFacts(grandFather).
relationFacts(grandmother).
relationFacts(grandson).
relationFacts(son).
relationFacts(uncle).
relationFacts(married).
relationFacts(maternaluncle).
relationFacts(siblings).
relationFacts(ancestor).
relationFacts(nephew).
relationFacts(wife).
relationFacts(husband).
relationFacts(motherinlaw).
relationFacts(fatherinlaw).
relationFacts(soninlaw).
relationFacts(daughterinlaw).
relationFacts(grandchild).
relationFacts(maternalgrandFather).
relationFacts(maternalgrandmother).
relationFacts(aunt).
relationFacts(brotherinlaw).
relationFacts(sisterinlaw).
relationFacts(cousin).
relationFacts(daughter).
relationFacts(maternalaunt).
relationFacts(findRelationship).