/******************************************************************************
    HashTables_SeparateChaining.c
	===========================
	
	* Separate Chaining is a key conflict resolution technique, where in two keys 
	after applying hash function lie on the same array index.
	
	* To resolve this issue, we maintain a linked list on each array index where 
	all the keys reaching on the same array index are maintained in a Singly 
	Linked List.

	public class SeparateChainingHashST<Key, Value>
	{
		private int M = 97; // number of chains
		private Node[] st = new Node[M]; // array of chains
	
		private static class Node
		{
			 private Object key;
			 private Object val;
			 private Node next;
			 ...
		}
	 
		private int hash(Key key)
		{ 
			return (key.hashCode() & 0x7fffffff) % M; 
		}
	 
		public Value get(Key key) {
			int i = hash(key);
			for (Node x = st[i]; x != null; x = x.next)
			if (key.equals(x.key)) return (Value) x.val;
			return null;
		}
		
		public void put(Key key, Value val) {
			int i = hash(key);
			for (Node x = st[i]; x != null; x = x.next)
			if (key.equals(x.key)) { x.val = val; return; }
			st[i] = new Node(key, val, st[i]);
		}
	}	
		
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0



int main()
{
	
	
	getch();
    return 0;
}
