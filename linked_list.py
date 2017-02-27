class Node(object):
	def __init__(self):
		self.data = None;
		self.next = None;
		self.prev = None;

	def __init__(self):
		self.data = None;
		self.next = None;
		self.prev = None;
		
	def __str__(self):
		return str(self.data);
		
	
		
class LinkedList(object):
	def __init__(self):
		self.head = None;
		self.tail = None;
		self.size = 0;
		
	def add(self, to_add):
		if self.size == 0:
			self.head = to_add;
			self.tail = to_add;
		else:
			self.tail.next = to_add;
			to_add.prev = self.tail;
			self.tail = to_add;
		self.size += 1;

	def add(self, to_add, pos):
		if self.size < pos or pos < 0:
			raise ValueError("index " + str(pos) + " is not in the linked list");
		
		node = head;
		while node.next != None and pos != 0:
			node = node.next;
		
		to
		
				
	def remove(self, to_del):
		to_del.prev.next = to_del.next;
		to_del.next.prev = to_del.prev;
		self.size -= 1;


first = Node();

first.data = 5;

ll = LinkedList();
ll.add(first);


blah = Node();

ll.add(blah);
 
print(first);
