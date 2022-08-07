#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

namespace rust {
	inline namespace cxxbridge1 {
		// #include "rust/cxx.h"

		struct unsafe_bitcopy_t;

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
		class String final {
		public:
			String() noexcept;
			String(const String&) noexcept;
			String(String&&) noexcept;
			~String() noexcept;

			String(const std::string&);
			String(const char*);
			String(const char*, std::size_t);
			String(const char16_t*);
			String(const char16_t*, std::size_t);

			static String lossy(const std::string&) noexcept;
			static String lossy(const char*) noexcept;
			static String lossy(const char*, std::size_t) noexcept;
			static String lossy(const char16_t*) noexcept;
			static String lossy(const char16_t*, std::size_t) noexcept;

			String& operator=(const String&) &noexcept;
			String& operator=(String&&) &noexcept;

			explicit operator std::string() const;

			const char* data() const noexcept;
			std::size_t size() const noexcept;
			std::size_t length() const noexcept;
			bool empty() const noexcept;

			const char* c_str() noexcept;

			std::size_t capacity() const noexcept;
			void reserve(size_t new_cap) noexcept;

			using iterator = char*;
			iterator begin() noexcept;
			iterator end() noexcept;

			using const_iterator = const char*;
			const_iterator begin() const noexcept;
			const_iterator end() const noexcept;
			const_iterator cbegin() const noexcept;
			const_iterator cend() const noexcept;

			bool operator==(const String&) const noexcept;
			bool operator!=(const String&) const noexcept;
			bool operator<(const String&) const noexcept;
			bool operator<=(const String&) const noexcept;
			bool operator>(const String&) const noexcept;
			bool operator>=(const String&) const noexcept;

			void swap(String&) noexcept;

			String(unsafe_bitcopy_t, const String&) noexcept;

		private:
			struct lossy_t;
			String(lossy_t, const char*, std::size_t) noexcept;
			String(lossy_t, const char16_t*, std::size_t) noexcept;
			friend void swap(String& lhs, String& rhs) noexcept { lhs.swap(rhs); }

			std::array<std::uintptr_t, 3> repr;
		};
#endif // CXXBRIDGE1_RUST_STRING
	} // namespace cxxbridge1
} // namespace rust

namespace com {
	namespace cross_platform_lib {
		struct Quaternion;
		struct ObjInfo;
	}
}

namespace com {
	namespace cross_platform_lib {
#ifndef CXXBRIDGE1_STRUCT_com$cross_platform_lib$Quaternion
#define CXXBRIDGE1_STRUCT_com$cross_platform_lib$Quaternion
		struct Quaternion final {
			float x;
			float y;
			float z;
			float w;

			using IsRelocatable = ::std::true_type;
		};
#endif // CXXBRIDGE1_STRUCT_com$cross_platform_lib$Quaternion

#ifndef CXXBRIDGE1_STRUCT_com$cross_platform_lib$ObjInfo
#define CXXBRIDGE1_STRUCT_com$cross_platform_lib$ObjInfo
		struct ObjInfo final {
			::rust::String name;
			float age;
			::rust::String desc;

			using IsRelocatable = ::std::true_type;
		};
#endif // CXXBRIDGE1_STRUCT_com$cross_platform_lib$ObjInfo

		extern "C" ::std::size_t add(::std::size_t left, ::std::size_t right) noexcept;

		extern "C" ::com::cross_platform_lib::Quaternion gen_quaternion(float x, float y, float z, float w) noexcept;

		::com::cross_platform_lib::ObjInfo gen_obj_info(::rust::String name, float age, ::rust::String desc) noexcept;

		::rust::String gen_obj_info_str(::rust::String name, float age, ::rust::String desc) noexcept;
	} // namespace cross_platform_lib
} // namespace com
