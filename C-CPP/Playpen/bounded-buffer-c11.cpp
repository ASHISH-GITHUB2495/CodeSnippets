#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

std::mutex cont_mu;

struct BoundedBuffer {
	int* buffer;
	int capacity;

	int front;
	int rear;
	int count;

	std::mutex lock;

	std::condition_variable not_full;
	std::condition_variable not_empty;

	BoundedBuffer(int capacity) : capacity(capacity), front(0), rear(0), count(0) {
		buffer = new int[capacity];
	}

	~BoundedBuffer() {
		delete[] buffer;
	}

	void deposit(int data) {
		std::unique_lock<std::mutex> l(lock);

		not_full.wait(l, [this]() {return count != capacity; });

		buffer[rear] = data;
		rear = (rear + 1) % capacity;
		++count;

		not_empty.notify_one();
	}

	int fetch() {
		std::unique_lock<std::mutex> l(lock);

		not_empty.wait(l, [this]() {return count != 0; });

		int result = buffer[front];
		front = (front + 1) % capacity;
		--count;

		not_full.notify_one();

		return result;
	}
};


void consumer(int id, BoundedBuffer& buffer) {
	for (int i = 0; i < 50; ++i) {
		int value = buffer.fetch();
		cont_mu.lock();
		std::cout << "Consumer " << id << " fetched " << value << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		cont_mu.unlock();
	}
}

void producer(int id, BoundedBuffer& buffer) {
	for (int i = 0; i < 75; ++i) {
		buffer.deposit(i);
		cont_mu.lock();
		std::cout << "Produced " << id << " produced " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		cont_mu.unlock();
	}
}

int main() {
	BoundedBuffer buffer(200);

	std::thread c1(consumer, 0, std::ref(buffer));
	std::thread c2(consumer, 1, std::ref(buffer));
	std::thread c3(consumer, 2, std::ref(buffer));
	std::thread p1(producer, 0, std::ref(buffer));
	std::thread p2(producer, 1, std::ref(buffer));

	c1.join();
	c2.join();
	c3.join();
	p1.join();
	p2.join();

	return 0;
}