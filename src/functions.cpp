#include "functions.h"


long double get_the_value_of_the_math_function_at_a_point (long double point) {

    return sin (point);
}

long double get_the_value_of_the_derivative_of_the_math_function_at_a_point (long double point) {

    return cos (point);
}

void get_the_array_of_the_derivatives_at_a_points_of_a_grid (
    long double* &par_x,
    long double* &par_y,
    long double* &par_math_derivative,
    long double* &par_nm_derivative,
    const size_t par_M,
    const long double par_a,
    const long double par_h) {

    par_x[0] = par_a;
    par_y[0] = get_the_value_of_the_math_function_at_a_point (par_a);
    par_math_derivative[0] = get_the_value_of_the_derivative_of_the_math_function_at_a_point (par_x[0]);
    for (size_t i = 1; i < par_M; ++i) {
        par_x[i] = par_x[i-1] + par_h;
        par_y[i] = get_the_value_of_the_math_function_at_a_point (par_x[i]);
        par_math_derivative[i] = get_the_value_of_the_derivative_of_the_math_function_at_a_point (par_x[i]);
    }

    par_nm_derivative[0] = (-3 * par_y[0] + 4 * par_y[1] - par_y[2]) / (2 * par_h);
    par_nm_derivative[par_M-1] = (3 * par_y[par_M-1] - 4 * par_y[par_M-2] + par_y[par_M-3]) / (2 * par_h);

    for (size_t i = 1; i < par_M - 1; ++i)
        par_nm_derivative[i] = (par_y[i+1] - par_y[i-1]) / (2 * par_h);
}

void evaluating_errors_for_two_vectors (
    const long double *accurate_values,
    const long double *approximate_values,
    const size_t number_of_values,
    long double* &result) {

    long double abs_error_1 = 0.0, abs_error_2 = 0.0, abs_error_inf = abs (accurate_values[0] - approximate_values[0]);
    long double norm_of_vector_in_denominator_1 = 0.0, norm_of_vector_in_denominator_2 = 0.0, norm_of_vector_in_denominator_inf = abs (accurate_values[0]);
    for (size_t i = 0; i < number_of_values; ++i) {
        long double difference = abs (accurate_values[i] - approximate_values[i]);
        abs_error_1 += difference;
        abs_error_2 += pow (difference, 2);
        if (abs_error_inf < difference)
            abs_error_inf = difference;

        norm_of_vector_in_denominator_1 += abs (accurate_values[i]);
        norm_of_vector_in_denominator_2 += pow (accurate_values[i], 2.);
        if (norm_of_vector_in_denominator_inf < accurate_values[i])
            norm_of_vector_in_denominator_inf = accurate_values[i];
    }
    abs_error_2 = sqrt (abs_error_2);
    norm_of_vector_in_denominator_2 = sqrt (norm_of_vector_in_denominator_2);

    result[0] = abs_error_1;
    result[1] = abs_error_2;
    result[2] = abs_error_inf;
    result[3] = abs_error_1 / norm_of_vector_in_denominator_1;
    result[4] = abs_error_2 / norm_of_vector_in_denominator_2;
    result[5] = abs_error_inf / norm_of_vector_in_denominator_inf;
}

void evaluate_and_print_errors_as_a_table (
    const long double* par_math_derivative,
    const long double* par_nm_derivative,
    const long double* par_shredded_math_derivative,
    const long double* par_shredded_nm_derivative,
    const long double* par_updated_runge_solution,
    const long double* par_runge_main_members,
    const size_t par_M,
    const size_t par_shredded_M) {

    long double* errors_grid_h = new long double [6];
    long double* errors_grid_half_h = new long double [6];
    long double* errors_update_runge_solution = new long double [6];

    evaluating_errors_for_two_vectors (par_math_derivative, par_nm_derivative, par_M, errors_grid_h);
    evaluating_errors_for_two_vectors (par_shredded_math_derivative, par_shredded_nm_derivative, par_shredded_M, errors_grid_half_h);
    evaluating_errors_for_two_vectors (par_math_derivative, par_updated_runge_solution, par_M, errors_update_runge_solution);

    // Part I: paragraph 7 - printing errors //
    cout << "\n         table 1: paragraph 7 - printing errors" << endl;
    for (size_t i = 0; i < 60; ++i)
        cout << "–";
    cout << "\n";

    cout << '|' << setw (23) << '|';
    cout << setw (11) << "     h     " << '|';
    cout << setw (11) << "   h / 2   " << '|';
    cout << setw (11) << "   Runge   " << '|';
    cout << "\n";

    for (size_t i = 0; i < 60; ++i)
        cout << "–";
    cout << "\n";

    cout << left;              // alignment
    cout << scientific;        // floating-point output
    cout << setprecision (3);  // precision 

    for (size_t i = 0; i < 6; ++i) {
        if (i < 3)
            cout << "| Absolute error  (" << i + 1 << ")  | ";
        else
            cout << "| Relative error  (" << i - 2 << ")  | ";

        cout << setw (6) << errors_grid_h[i] << " | ";
        cout << setw (6) << errors_grid_half_h[i] << " | ";
        cout << setw (6) << errors_update_runge_solution[i] << " | ";
        cout << "\n";

        for (size_t j = 0; j < 60; ++j)
            cout << "–";
        cout << "\n";
    }

    // Part II: paragraph 8 - compare errors //

    long double runge_norm_1 = 0.0, runge_norm_2 = 0.0, runge_norm_inf = abs (par_runge_main_members[0]);

    for (size_t i = 0; i < par_M; ++i) {
        // long double difference = abs (accurate_values[i] - approximate_values[i]);
        runge_norm_1 += abs (par_runge_main_members[i]);
        runge_norm_2 += pow (par_runge_main_members[i], 2);
        if (runge_norm_inf < abs (par_runge_main_members[i]))
            runge_norm_inf = abs (par_runge_main_members[i]);
    }
    runge_norm_2 = sqrt (runge_norm_2);

    cout << "\n\n                table 2: paragraph 8 - compare errors" << endl;

    for (size_t i = 0; i < 72; ++i)
        cout << "–";
    cout << "\n";

    cout << '|' << "                      " << '|';
    cout << setw (11) << "     h     " << '|';
    cout << setw (11) << "   h / 2   " << '|';
    cout << setw (11) << "   Runge   " << '|';
    cout << setw (11) << "main member" << '|';
    cout << "\n";

    for (size_t i = 0; i < 72; ++i)
        cout << "–";
    cout << "\n";
    for (size_t i = 0; i < 3; ++i) {
        cout << "| Absolute error  (" << i + 1 << ")  | ";

        cout << setw (6) << errors_grid_h[i] << " | ";
        cout << setw (6) << errors_grid_half_h[i] << " | ";
        cout << setw (6) << errors_update_runge_solution[i] << " | ";
        if (i == 0)
            cout << setw (6) << runge_norm_1 << " | ";
        if (i == 1)
            cout << setw (6) << runge_norm_2 << " | ";
        if (i == 2)
            cout << setw (6) << runge_norm_inf << " | ";
        cout << "\n";

        for (size_t j = 0; j < 72; ++j)
            cout << "–";
        cout << "\n";
    }

    delete [] errors_grid_h;
    delete [] errors_grid_half_h;
    delete [] errors_update_runge_solution;
}

void extract_data_to_the_file (
    const long double* par_math_derivative,
    const size_t par_M_viz,
    const long double* par_x,
    const long double* par_nm_derivative,
    const size_t par_M,
    const long double* par_shredded_x,
    const long double* par_shredded_nm_derivative,
    const size_t par_shredded_M,
    const long double* par_updated_runge_solution,
    const string par_filename) {

    // export data to the file //
    ofstream file;
    file.open (par_filename);
    
    file << par_M_viz << '\n' << par_M << '\n' << par_shredded_M << '\n';

    const long double h_viz = abs (par_x[0] - par_x[par_M-1]) / (par_M_viz - 1);
    long double x_viz = par_x[0];

    // extract data for math_derivative (M_viz) //
    for (size_t i = 0; i < par_M_viz; ++i) {
        file <<  x_viz + h_viz * i << ' ';
    }
    file << '\n';
    x_viz = par_x[0];
    for (size_t i = 0; i < par_M_viz; ++i) {
        file << get_the_value_of_the_derivative_of_the_math_function_at_a_point (x_viz + h_viz * i) << ' ';
    }
    file << '\n';

    // extract data for numerical derivative with step h (M)//
    for (size_t i = 0; i < par_M; ++i) {
        file << par_x[i] << ' ';
    }
    file << '\n';
    for (size_t i = 0; i < par_M; ++i) {
        file << par_nm_derivative[i] << ' ';
    }
    file << '\n';

    // extract data for numerical derivative with step 0.5h (shredded_M)//
    for (size_t i = 0; i < par_shredded_M; ++i) {
        file << par_shredded_x[i] << ' ';
    }
    file << '\n';
    for (size_t i = 0; i < par_shredded_M; ++i) {
        file << par_shredded_nm_derivative[i] << ' ';
    }
    file << '\n';

    // extract data for updated Runge solution (M) //
    for (size_t i = 0; i < par_M; ++i) {
        file << par_updated_runge_solution[i] << ' ';
    }
    file << '\n';
    
    file.close ();
}