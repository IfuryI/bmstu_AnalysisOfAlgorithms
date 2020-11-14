#include "rtx.h"


#include "camera.h"
#include "color.h"
#include "constant_medium.h"
#include "moving_sphere.h"
#include "sphere.h"
#include "texture.h"

#include <iostream>
#include <thread>
#include <fstream>


color ray_color(const ray& r, const color& background, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return color(0,0,0);

    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}


hittable_list random_scene() {
    hittable_list world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                            center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return hittable_list(make_shared<bvh_node>(world, 0.0, 1.0));
}

void seq()
{
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 5;
    int max_depth = 2;

    hittable_list world;

    point3 lookfrom;
    point3 lookat;
    auto vfov = 40.0;
    auto aperture = 0.0;
    color background(0,0,0);

    world = random_scene();
    background = color(0.70, 0.80, 1.00);
    lookfrom = point3(13,2,3);
    lookat = point3(0,0,0);
    vfov = 20.0;
    aperture = 0.1;

    const vec3 vup(0,1,0);
    const auto dist_to_focus = 10.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);


// Последовательное выполнение цикла
    std::ofstream out;
    out.open("img322.ppm");

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(out, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}

typedef struct color_buf
{
    int x1;
    int x2;
    int x3;

} color_buf;


// Цикл вычисляющий значения пикселов на поданном участке
void cycle(int x, int y, int endx, int endy, int samples_per_pixel, camera cam, color background, const hittable_list& world, int max_depth,
           int image_width, int image_height, color_buf *buf)
{
    for (int j = endx-1; j >= x; --j)
    {
        for (int i = endy; i < y; ++i) //  ГРАницы
        {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (j + random_double()) / (image_width-1);
                auto v = (i + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }

            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();


            if (r != r) r = 0.0;
            if (g != g) g = 0.0;
            if (b != b) b = 0.0;


            auto scale = 1.0 / samples_per_pixel;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            int offset = ((image_width) * i) + j;

            buf[offset].x1 = static_cast<int>(256 * clamp(r, 0.0, 0.999));
            buf[offset].x2 = static_cast<int>(256 * clamp(g, 0.0, 0.999));
            buf[offset].x3 = static_cast<int>(256 * clamp(b, 0.0, 0.999));

        }
    }
}

void parallel()
{
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 5;
    int max_depth = 2;

    hittable_list world;

    point3 lookfrom;
    point3 lookat;
    auto vfov = 40.0;
    auto aperture = 0.0;
    color background(0,0,0);

    world = random_scene();
    background = color(0.70, 0.80, 1.00);
    lookfrom = point3(13,2,3);
    lookat = point3(0,0,0);
    vfov = 20.0;
    aperture = 0.1;

    const vec3 vup(0,1,0);
    const auto dist_to_focus = 10.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);


// Подготовка данных для запуска параллельного выполнения цикла

    int n = 8; // Количество потоков

    int step = image_width / n;

    std::vector<std::thread *> threadArr;

    int x1 = 0;
    int x2 = step;

    int y1 = 0;
    int y2 = image_height;

    auto buf = new color_buf[image_width * image_height];
    for (int i = 0; i < image_width * image_height; i++)
    {
        buf[i].x1 = 0;
        buf[i].x2 = 0;
        buf[i].x3 = 0;
    }

    for (int i = 0; i < n; i++)
    {
        // Создаем поток 
        auto* newThread = new std::thread(cycle, x1, y2, x2, y1, samples_per_pixel, cam, background, world, max_depth, image_width, image_height, buf);
        threadArr.push_back(newThread);

        x1 = x2;
        x2 += step;
    }

    for (int i = 0; i < n; i++)
    {
        threadArr[i]->join();
    }

// Запись пикселов изображения из буфера (который наполняли разные потоки параллельно) в файл.
    std::ofstream out;
    out.open("img228.ppm");
    if (out.is_open())
    {
        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    }

    for (int i = 0; i < 90000; i++)
    {
        out << buf[i].x1 << ' ' << buf[i].x2 << ' ' << buf[i].x3 << "\n";
    }
}



int main()
{
    // Тестирование времени работы параллельного и последовательного алгоритма

    auto start = std::chrono::system_clock::now();
    {
        parallel();
//        seq();

    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << "s";
}