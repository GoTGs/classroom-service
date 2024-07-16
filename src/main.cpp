#include "../include/endpoints.hpp"
#include <thread>

int main(int argc, char** argv) {
	CppHttp::Net::Router router;
	CppHttp::Net::TcpListener server;
	server.CreateSocket();

	int requestCount = 0;

	auto onReceive = [&](CppHttp::Net::Request req) {
		router.Handle(req);
	};

	server.SetOnReceive(onReceive);

	router.AddRoute("POST", "/classroom/create", CreateClassroom);
	router.AddRoute("GET", "/classroom/user/get", GetUserClassrooms);

	server.Listen("0.0.0.0", 8002, std::thread::hardware_concurrency());

	Database::GetInstance()->Close();
}