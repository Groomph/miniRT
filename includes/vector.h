
typedef struct  s_vector
{
        long double     x;
        long double     y;
        long double     z;
}               t_vector;

t_vector        add_vectors(t_vector *vec1, t_vector *vec2);
t_vector        subtract_vectors(t_vector *vec1, t_vector *vec2);
t_vector        multiply_vectors(long double doub, t_vector *vec2);
t_vector        divide_vectors(long double doub, t_vector *vec2);

long double     get_scalar_product(t_vector *vec1, t_vector *vec2);
long double     get_norme(t_vector *vec1);
void        get_normalized(t_vector *vec1);
