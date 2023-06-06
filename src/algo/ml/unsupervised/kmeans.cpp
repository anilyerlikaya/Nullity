#include "kmeans.h"
#include <unordered_set>

nl::ml::KMeans::KMeans(int k): k(k) {
    // nothing
}

void nl::ml::KMeans::fit(nl::Matrix2d<float>& dataset) {
    int sample_size = dataset.height();
    if(k > sample_size)
        throw std::runtime_error("K value of KMeans must not be smaller than sample amount!\n");

    // random number generator 
    nl::random::rndm_generator engine(0, sample_size - 1);

    // random cluster initialization
    centroids = nl::Matrix2d<float>(dataset.width(), k);

    // get random indeces
    std::unordered_set<int> cluster_ids;
    while(cluster_ids.size() < k)
        cluster_ids.insert(engine.rndm_int_value());
    
    
    int i = 0;
    for (auto it = cluster_ids.begin(); it != cluster_ids.end(); it++) { 
        printf("%d. class_init_index: %d\n", i, *it);
        centroids.set_row(i, dataset.get_row_array(*it));
        i++;
    }

    for(int i=0; i<centroids.height(); i++) {
        printf("%d: ", i);
        for(int j=0; j<centroids.width(); j++) {
            printf("%lf ", centroids.get_point(i, j));
        }
        printf("\n");
    }

    // generate initial array
    nl::Array<int> labels(sample_size, 0);

    int iteration = 0;
    bool is_updated = true;
    while(is_updated) {
        if(iteration++ > max_iteration) {
            printf("WARNING! Cannot find stable centroids under limit of max iteration: %d!\n", max_iteration);
            break;
        }
        is_updated = false;

        // keep centroid updates
        nl::Matrix2d<float> new_centroids(centroids.width(), k);
        std::vector<float> membership_ct(k, 0);

        // assign labels according to centroids
        for(int i = 0; i<sample_size; i++) {
            nl::Array<float>& sample = dataset.get_row_array(i);
            float min_dist = MAX_FLOAT;
            int m_cluster_id = -1;
            for(int j=0; j<k; j++) {
                float cur_dist = sample.find_dist(centroids.get_row_array(j));
                if(cur_dist < min_dist) {
                    //printf("for sample %d, dist is upgraded from %lf to %lf for cluster %d\n", i, min_dist, cur_dist, j);
                    min_dist = cur_dist;
                    m_cluster_id = j;
                }
            }

            // cluster membership upgraded
            if(labels.get_point(i) != m_cluster_id) {
                labels.set_point(i, m_cluster_id);
                is_updated = true;
            }

            new_centroids.set_row(m_cluster_id, new_centroids.get_row_array(m_cluster_id) + sample);    
            membership_ct[m_cluster_id]++;    
        }

        // calculate new centroids
        for(int i=0; i<k; i++) 
            centroids.set_row(i, new_centroids.get_row_array(i) / membership_ct[i]);    
    } 
}

nl::Array<int> nl::ml::KMeans::predict(nl::Matrix2d<float>& dataset) {
    int sample_size = dataset.height();

    // generate initial array
    nl::Array<int> labels(sample_size, 0);

    for(int i = 0; i<sample_size; i++) {
        nl::Array<float>& sample = dataset.get_row_array(i);
        float min_dist = MAX_FLOAT;
        for(int j=0; j<k; j++) {
            float cur_dist = sample.find_dist(centroids.get_row_array(j));
            if(cur_dist < min_dist) {
                //printf("for sample %d, dist is upgraded from %lf to %lf for cluster %d\n", i, min_dist, cur_dist, j);
                min_dist = cur_dist;
                labels.set_point(i, j);
            }
        }
    }

    return labels;  
}
