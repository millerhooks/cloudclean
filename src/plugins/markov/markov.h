#ifndef MARKOV_H
#define MARKOV_H

#include "pluginsystem/iplugin.h"
#include "featurelist.h"
#include <boost/serialization/shared_ptr.hpp>
#include <pcl/features/principal_curvatures.h>
class QAction;
class QWidget;
class Core;
class CloudList;
class LayerList;
class FlatView;
class GLWidget;
class MainWindow;
class NormalEstimator;
class QVBoxLayout;
class QTableView;
class QDockWidget;
class QDoubleSpinBox;
class QSpinBox;

class Markov : public IPlugin {
    Q_INTERFACES(IPlugin)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "za.co.circlingthesun.cloudclean.iplugin" FILE "markov.json")
 public:
    QString getName();
    void initialize(Core * core);
    void initialize2(PluginManager * pm);
    void cleanup();

    ~Markov();

 private:
    void randomforest();

 signals:
    void enabling();

 public slots:
    void enable();
    void disable();


 private:
    Core * core_;
    CloudList * cl_;
    LayerList * ll_;
    GLWidget * glwidget_;
    FlatView * flatview_;
    MainWindow * mw_;

    NormalEstimator * ne_;

    QAction * enable_;
    QAction * forest_action_;

    QWidget * dock_widget_;
    QDockWidget * dock_;

    FeatureList * feature_list_;
    QTableView * feature_view_;

    QDoubleSpinBox * pca_radius_spinner_;
    QDoubleSpinBox * curvature_radius_spinner_;
    QDoubleSpinBox * octree_cell_size_spinner_;

    QSpinBox * tree_count_spinner_;
    QSpinBox * tree_depth_spinner_;

    double pca_radius_;
    double curvature_radius_;
    double octree_cell_size_;

    int tree_count_;
    int tree_depth_;

    pcl::PointCloud<pcl::PointXYZINormal>::Ptr smallcloud_;
    std::vector<int> big_to_small_;
    boost::shared_ptr<std::vector<Eigen::Vector3f> > pca_;
    pcl::PointCloud<pcl::PrincipalCurvatures>::Ptr principal_curvatures_;

    bool pca_dirty_ = true;
    bool curvatures_dirty_ = true;
    bool downsample_dirty_ = true;

    bool enabled_;
};

#endif  // MARKOV_H
