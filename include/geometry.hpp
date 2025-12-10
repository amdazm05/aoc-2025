#ifndef GEOMETRY
#define GEOMETRY

#include <concepts>
#include <type_traits>

namespace geo {
    template <typename T>
        requires std::is_arithmetic_v<T>
    struct point3D {
        T x{}, y{}, z{};
        constexpr point3D operator+(const point3D & r) {
            return {x+r.x,y+r.y,z+r.z};
        }

        constexpr point3D operator*(T s) {
            return {x*s,y*s,z*s};
        }
    };

    template <typename T>
        requires std::is_arithmetic_v<T>
    struct point2D {
        T x{}, y{};
        constexpr point2D operator+(const point2D & r) {
            return {x+r.x,y+r.y};
        }

        constexpr point2D operator*(T s) {
            return {x*s,y*s};
        }
    };
};

namespace geo_helpers {
    geo::point3D<uint64_t> get_coords_from_string (const std::string & input) {
        std::istringstream in;
        geo::point3D<uint64_t>  res;
        in.str(input);
        int i=0;
        try {
            for (std::string s; std::getline(in,s,',');i++) {
                if(s.empty()) continue;
                switch(i) {
                    case 0:
                        res.x=std::stoll(s);
                        break;
                    case 1:
                        res.y=std::stoll(s);
                        break;
                    case 2:
                        res.z=std::stoll(s);
                        break;
                    default:
                        throw std::runtime_error("This is not a 3D point");
                }
            }
        }
        catch (std::runtime_error e) {
            std::cout<<"geo_helpers error:"<<e.what()<<std::endl;
        }
        return res;
    }

    geo::point2D<uint64_t> get_coords_from_string_2D (const std::string & input) {
        std::istringstream in;
        geo::point2D<uint64_t>  res;
        in.str(input);
        int i=0;
        try {
            for (std::string s; std::getline(in,s,',');i++) {
                if(s.empty()) continue;
                switch(i) {
                    case 0:
                        res.x=std::stoll(s);
                        break;
                    case 1:
                        res.y=std::stoll(s);
                        break;
                    default:
                        throw std::runtime_error("This is not a 2D point");
                }
            }
        }
        catch (std::runtime_error e) {
            std::cout<<"geo_helpers error:"<<e.what()<<std::endl;
        }
        return res;
    }

    uint64_t to_point_distance_sqrd (const geo::point3D<uint64_t> & u, const geo::point3D<uint64_t> & v) {
        int64_t dx = u.x - v.x;
        int64_t dy = u.y - v.y;
        int64_t dz = u.z - v.z;
        return  uint64_t(dx*dx + dy*dy + dz*dz);
    }
}

#endif /* GEOMETRY */