class Ray;
class Hit;

class Hitable {
  public:
    virtual bool intersect(const Ray& ray, Hit& res) const = 0;  
};
