#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

int main()
{
	std::mutex m;
	std::condition_variable cv;
	int turn = 1;

	auto worker = [&](int id)
		{
			std::unique_lock<std::mutex> lk(m);
			// 自分の順番になるまで待つ
			cv.wait(lk, [&] { return turn == id; });

			std::cout << "thread " << id << std::endl;

			++turn;

			lk.unlock();
			cv.notify_all();
		};

	std::vector<std::thread> threads;

	for (int i = 1; i <= 3; ++i)
	{
		threads.emplace_back(worker, i);
	}


	for (auto& t : threads)
	{
		t.join();
	}

	return 0;
}