
#include "HittableList.h"
#include "Sphere.h"

using std::make_unique;

bool HittableList::Hit(const Ray3& r, 
					   double t_min, 
					   double t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max; // very clever!

    for (const auto& object : objects) 
    {
        if (object->Hit(r, t_min, closest_so_far, temp_rec)) 
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

void HittableList::CreateWorld()
{
    objects.push_back(make_unique<Sphere>(Point3(0, 0, -1), 0.5));
    objects.push_back(make_unique<Sphere>(Point3(0, -100.5, -1), 100));
}

