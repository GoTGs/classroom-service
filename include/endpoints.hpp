#pragma once

#include "CppHttp.hpp"
#include "database.hpp"
#include "jwt-cpp/traits/nlohmann-json/traits.h"
#include <iostream>
#include <string>
#include <tuple>
#include <optional>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <variant>

using returnType = std::tuple<CppHttp::Net::ResponseType, std::string, std::optional<std::vector<std::string>>>;
using json = nlohmann::json;

struct User {
	int id;
	std::string email;
	std::string password;
	std::string salt;
	std::string firstName;
	std::string lastName;
    std::string role;
};

struct Classroom {
    int id;
    std::string name;
    int ownerId;
};

struct ClassroomUser {
    int id;
    int classroomId;
    int userId;
};

struct TokenError {
    CppHttp::Net::ResponseType type;
    std::string message;
};

namespace soci
{
    template<>
    struct type_conversion<User>
    {
        typedef values base_type;

        static void from_base(values const& v, indicator /* ind */, User& u)
        {
            u.id = v.get<int>("id", 0);
            u.email = v.get<std::string>("email");
            u.password = v.get<std::string>("password");
            u.salt = v.get<std::string>("salt");
            u.firstName = v.get<std::string>("first_name");
            u.lastName = v.get<std::string>("last_name");
            u.role = v.get<std::string>("role");
        }

        static void to_base(const User& u, values& v, indicator& ind)
        {
            v.set("id", u.id);
            v.set("email", u.email);
            v.set("password", u.password);
            v.set("salt", u.salt);
            v.set("first_name", u.firstName);
            v.set("last_name", u.lastName);
            v.set("role", u.role);
            ind = i_ok;
        }
    };

    template<>
    struct type_conversion<Classroom>
    {
		typedef values base_type;

        static void from_base(values const& v, indicator /* ind */, Classroom& c)
        {
			c.id = v.get<int>("id", 0);
			c.name = v.get<std::string>("name");
			c.ownerId = v.get<int>("owner_id");
		}

        static void to_base(const Classroom& c, values& v, indicator& ind)
        {
			v.set("id", c.id);
			v.set("name", c.name);
			v.set("owner_id", c.ownerId);
			ind = i_ok;
		}
	};
}

std::variant<TokenError, json> ValidateToken(std::string& token);

returnType CreateClassroom(CppHttp::Net::Request req);

returnType AddUserToClassroom(CppHttp::Net::Request req);

returnType GetUserClassrooms(CppHttp::Net::Request req);

returnType GetClassroom(CppHttp::Net::Request req);

returnType GetClassroomMembers(CppHttp::Net::Request req);

returnType RenameClassroom(CppHttp::Net::Request req);

returnType RemoveUserFromClassroom(CppHttp::Net::Request req);

returnType DeleteClassroom(CppHttp::Net::Request req);