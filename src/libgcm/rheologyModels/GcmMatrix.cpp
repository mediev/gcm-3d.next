#include "libgcm/rheologyModels/GcmMatrix.hpp"
#include "libgcm/util/Assertion.hpp"

// For fabs())
#include <cmath>
// For memset())
#include <cstring>

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

using namespace gcm;

GcmMatrix::GcmMatrix(uchar size)
{
    INIT_LOGGER("gcm.GcmMatrix");
    this->size = size;
    p = new gcm::real*[size];
    for(int i = 0; i < size; i++) {
        p[i] = new gcm::real[size];
    }
};

GcmMatrix::~GcmMatrix()
{
    for(int i = 0; i < size; i++) {
        delete[] p[i];
    }
    delete[] p;
};

uchar GcmMatrix::getSize() const {
    return size;
};

GcmMatrix& GcmMatrix::operator=(const GcmMatrix &A)
{
    assert_true(size == A.size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            p[i][j] = A.p[i][j];
    return *this;
};

gcm::real& GcmMatrix::operator()(int i, int j)
{
    return p[i][j];
};

gcm::real GcmMatrix::get(int i, int j) const
{
    return p[i][j];
};

void GcmMatrix::createE()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            p[i][j] = (i == j ? 1 : 0);
};

bool GcmMatrix::operator==(const GcmMatrix &A) const
{
    assert_true(size == A.size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            // If element is greater than chosen floating point epsilon ...
            if ( (fabs(p[i][j]) > EQUALITY_TOLERANCE || fabs(A.p[i][j]) > EQUALITY_TOLERANCE )
                        // .. and difference is greater than 1% ...
                        && fabs(p[i][j] - A.p[i][j]) > 0.005 * fabs(p[i][j] + A.p[i][j]))
            {
                // .. matrices are not equal
                return false;
            }
    return true;
};

bool GcmMatrix::operator!=(const GcmMatrix &A) const
{
    return !(*this == A);
};

GcmMatrix GcmMatrix::operator*(const GcmMatrix &A) const
{
    assert_true(size == A.size);
    GcmMatrix res_matrix(size);
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            res_matrix.p[r][c] = 0;
            for (int i = 0; i < size; i++) {
                res_matrix.p[r][c] += this->p[r][i] * A.p[i][c];
            }
        }
    }
    return res_matrix;
};

GcmMatrix GcmMatrix::operator/(const GcmMatrix &A) const
{
    assert_true(size == A.size);
    return (*this * A.inv());
};

GcmMatrix GcmMatrix::operator*(const gcm::real &a) const
{
    GcmMatrix res_matrix(size);
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            res_matrix.p[r][c] = this->p[r][c] * a;
        }
    }
    return res_matrix;
};

GcmMatrix GcmMatrix::operator/(const gcm::real &a) const
{
    if( a == 0.0 )
        THROW_INVALID_ARG("Can not divide matrix by zero");
    return (*this * (1/a));
};

GcmMatrix GcmMatrix::operator%(const GcmMatrix &A) const
{
    assert_true(size == A.size);
    GcmMatrix res_matrix(size);
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            res_matrix.p[r][c] = this->p[r][c] / A.p[r][c];
        }
    }
    return res_matrix;
};

GcmMatrix GcmMatrix::operator+(const GcmMatrix &A) const
{
    assert_true(size == A.size);
    GcmMatrix res_matrix(size);
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            res_matrix.p[r][c] = this->p[r][c] + A.p[r][c];
    return res_matrix;
};

GcmMatrix GcmMatrix::operator-(const GcmMatrix &A) const
{
    assert_true(size == A.size);
    GcmMatrix res_matrix(size);
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            res_matrix.p[r][c] = this->p[r][c] - A.p[r][c];
    return res_matrix;
};

void GcmMatrix::clear()
{
    memset(p, 0, size * size * sizeof (gcm::real));
};

void GcmMatrix::setColumn(gcm::real *Clmn, int num)
{
    for (int i = 0; i < size; i++)
        p[i][num] = Clmn[i];
};

GcmMatrix GcmMatrix::inv() const
{
    GcmMatrix res_matrix(size);
    // Invert the matrix using gsl library

    gsl_set_error_handler_off();

    gsl_matrix* Z1 = gsl_matrix_alloc(size, size);
    gsl_matrix* Z = gsl_matrix_alloc(size, size);
    gsl_permutation* perm = gsl_permutation_alloc(size);
    int k;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            gsl_matrix_set(Z1, i, j, p[i][j]);

    int status = gsl_linalg_LU_decomp(Z1, perm, &k);
    if (status) {
        LOG_DEBUG("gsl_linalg_LU_decomp failed");
        THROW_INVALID_ARG("gsl_linalg_LU_decomp failed");
    }
    status = gsl_linalg_LU_invert(Z1, perm, Z);
    if (status) {
        LOG_DEBUG("gsl_linalg_LU_invert failed");
        THROW_INVALID_ARG("gsl_linalg_LU_invert failed");
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            res_matrix.p[i][j] = gsl_matrix_get(Z, i, j);

    gsl_permutation_free(perm);
    gsl_matrix_free(Z);
    gsl_matrix_free(Z1);

    return res_matrix;
};