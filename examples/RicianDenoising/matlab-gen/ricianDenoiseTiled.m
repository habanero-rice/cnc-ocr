function u = ricianDenoiseTiled(imageTiled, blockSize, sigma, lambda) %#codegen

    tileRows = sizeX(imageTiled, 1);
    tileCols = sizeX(imageTiled, 2);

    % Maximum allowed number of iterations
    maxIter = 100;
    % Gradient descent time step sizeX
    dt = 5;
    % Small parameter to avoid divide-by-zero
    epsilon = 1e-20;
    %sigma2 = sigma ^ 2;
    sigma2 = sigma * sigma;
    gamma = lambda / sigma2;

    % Initialize u as the input image
    u = imageTiled;

    ut = zeros(tileRows, tileCols, blockSize, blockSize);
    ur = zeros(tileRows, tileCols, blockSize, blockSize);
    ud = zeros(tileRows, tileCols, blockSize, blockSize);
    ul = zeros(tileRows, tileCols, blockSize, blockSize);

    g = zeros(tileRows, tileCols, blockSize, blockSize);
    r = zeros(tileRows, tileCols, blockSize, blockSize);
    ug = zeros(tileRows, tileCols, blockSize, blockSize);

    %%% Main gradient descent loop %%%
    for Iter = 1:maxIter

        % value of u from the previous iteration
        ulast = u;

        % Create shifted versions of the image
        for i = 1:tileRows
            for j = 1:tileCols

                % Compute U offsets for top, right, down, and left.

                ulast_cur = reshape(ulast(i, j, :, :), blockSize, blockSize);

                ulast_top = ulast_cur;
                if i > 1
                    ulast_top = reshape(ulast(i-1, j, :, :), blockSize, blockSize);
                end

                ulast_rig = ulast_cur;
                if j > 1
                    ulast_rig = reshape(ulast(i, j-1, :, :), blockSize, blockSize);
                end

                ulast_dow = ulast_cur;
                if i < tileRows
                    ulast_dow = reshape(ulast(i+1, j, :, :), blockSize, blockSize);
                end

                ulast_lef = ulast_cur;
                if j < tileCols
                    ulast_lef = reshape(ulast(i, j+1, :, :), blockSize, blockSize);
                end

                [rut, rur, rud, rul] = uDiffStep(i, j, blockSize, tileRows, tileCols, ulast_cur, ulast_top, ulast_rig, ulast_dow, ulast_lef);

                ut(i, j, :, :) = rut;
                ur(i, j, :, :) = rur;
                ud(i, j, :, :) = rud;
                ul(i, j, :, :) = rul;

            end
        end

        for i = 1:tileRows
            for j = 1:tileCols

                % Compute G

                u_ij  = reshape(ulast(i, j, :, :), blockSize, blockSize);
                ut_ij = reshape(ut(i, j, :, :), blockSize, blockSize);
                ur_ij = reshape(ur(i, j, :, :), blockSize, blockSize);
                ud_ij = reshape(ud(i, j, :, :), blockSize, blockSize);
                ul_ij = reshape(ul(i, j, :, :), blockSize, blockSize);

                g_temp = gStep(i, j, blockSize, u_ij, ut_ij, ur_ij, ud_ij, ul_ij, epsilon);
                g(i, j, :, :) = reshape(g_temp, 1, 1, blockSize, blockSize);

            end
        end

        for i = 1:tileRows
            for j = 1:tileCols

                % Compute R

                u_ij = reshape(ulast(i, j, :, :), blockSize, blockSize);
                img_ij = reshape(imageTiled(i, j, :, :), blockSize, blockSize);

                r_temp = rStep(i, j, blockSize, u_ij, img_ij, sigma2);
                r(i, j, :, :) = reshape(r_temp, 1, 1, blockSize, blockSize);

            end
        end

        for i = 1:tileRows
            for j = 1:tileCols

                % Compute UG

                % Update u by a semi-implicit step
                u_ij = reshape(ulast(i, j, :, :), blockSize, blockSize);
                g_ij = reshape(g(i, j, :, :), blockSize, blockSize);

                ug_temp = ugStep(i, j, blockSize, u_ij, g_ij);
                ug(i, j, :, :) = reshape(ug_temp, 1, 1, blockSize, blockSize);

            end
        end

        for i = 1:tileRows
            for j = 1:tileCols

                % Compute U

                ug_cur = reshape(ug(i, j, :, :), blockSize, blockSize);

                ug_top = ug_cur;
                if i > 1
                    ug_top = reshape(ug(i-1, j, :, :), blockSize, blockSize);
                end

                ug_rig = ug_cur;
                if j > 1
                    ug_rig = reshape(ug(i, j-1, :, :), blockSize, blockSize);
                end

                ug_dow = ug_cur;
                if i < tileRows
                    ug_dow = reshape(ug(i+1, j, :, :), blockSize, blockSize);
                end

                ug_lef = ug_cur;
                if j < tileCols
                    ug_lef = reshape(ug(i, j+1, :, :), blockSize, blockSize);
                end



                % gt = zeros(tileRows, tileCols);
                if i == 1
                    gt = reshape(g(i, j, :, :), blockSize, blockSize);
                else
                    gt = reshape(g(i-1, j, :, :), blockSize, blockSize);
                end

                % gr = zeros(tileRows, tileCols);
                if j == 1
                    gr = reshape(g(i, j, :, :), blockSize, blockSize);
                else
                    gr = reshape(g(i, j-1, :, :), blockSize, blockSize);
                end

                % gd = zeros(tileRows, tileCols);
                if i == tileRows
                    gd = reshape(g(i, j, :, :), blockSize, blockSize);
                else
                    gd = reshape(g(i+1, j, :, :), blockSize, blockSize);
                end

                % gl = zeros(tileRows, tileCols);
                if j == tileCols
                    gl = reshape(g(i, j, :, :), blockSize, blockSize);
                else
                    gl = reshape(g(i, j+1, :, :), blockSize, blockSize);
                end

                u_ij = reshape(ulast(i, j, :, :), blockSize, blockSize);
                img_ij = reshape(imageTiled(i, j, :, :), blockSize, blockSize);
                r_ij = reshape(r(i, j, :, :), blockSize, blockSize);

                u_temp = uStep(i, j, blockSize, tileRows, tileCols, ug_cur, ug_top, ug_rig, ug_dow, ug_lef, gt, gr, gd, gl, u_ij, img_ij, r_ij, gamma, dt);
                u(i, j, :, :) = reshape(u_temp, 1, 1, blockSize, blockSize);

            end
        end

    end



function g = gStep(i, j, blockSize, u_ij, ut_ij, ur_ij, ud_ij, ul_ij, epsilon) %#codegen

    g = zeros(blockSize, blockSize);

    eut = ut_ij - u_ij;
    eur = ur_ij - u_ij;
    eud = ud_ij - u_ij;
    eul = ul_ij - u_ij;

    err = epsilon +        ...
            eut .* eut +   ...
            eur .* eur +   ...
            eud .* eud +   ...
            eul .* eul ;

    % Approximate 1/|grad u|
    g = 1 ./ sqrt(err);



function ug = ugStep(i, j, blockSize, u_ij, g_ij) %#codegen
    ug = zeros(blockSize, blockSize);
    ug = u_ij .* g_ij;



function r = rStep(i, j, blockSize, u_ij, img_ij, sigma2) %#codegen

    r = zeros(blockSize, blockSize);
    % Evaluate I1(inImage.*u/sigma^2) ./ I0(inImage.*u/sigma^2)
    r_temp = u_ij .* img_ij / sigma2;
    % Rational approximation of I1(r)./I0(r): Approximation is L^inf
    % optimal with error less than 8e-4 for all x >= 0.
    numerator = ( r_temp .* (2.38944 + r_temp .* (0.950037 + r_temp)) );
    denominator = ( 4.65314 + r_temp .* (2.57541 + r_temp .* (1.48937 + r_temp)) );
    r = numerator ./ denominator;



function [ut, ur, ud, ul] = uDiffStep(i, j, blockSize, tileRows, tileCols, ulast_cur, ulast_top, ulast_rig, ulast_dow, ulast_lef) %#codegen

    ut = zeros(blockSize, blockSize);
    ur = zeros(blockSize, blockSize);
    ud = zeros(blockSize, blockSize);
    ul = zeros(blockSize, blockSize);

    ut(2:blockSize, :) = ulast_cur(1:blockSize-1, :);
    if i == 1
        ut(1, :) = ulast_cur(1, :);
    else
        ut(1, :) = ulast_top(blockSize, :);
    end

    ur(:, 2:blockSize) = ulast_cur(:, 1:blockSize-1);
    if j == 1
        ur(:, 1) = ulast_cur(:, 1);
    else
        ur(:, 1) = ulast_rig(:, blockSize);
    end

    ud(1:blockSize-1, :) = ulast_cur(2:blockSize, :);
    if i == tileRows
        ud(blockSize, :) = ulast_cur(blockSize, :);
    else
        ud(blockSize, :) = ulast_dow(1, :);
    end

    ul(:, 1:blockSize-1) = ulast_cur(:, 2:blockSize);
    if j == tileCols
        ul(:, blockSize) = ulast_cur(:, blockSize);
    else
        ul(:, blockSize) = ulast_lef(:, blockSize);
    end



function u = uStep(i, j, blockSize, tileRows, tileCols, ug_cur, ug_top, ug_rig, ug_dow, ug_lef, gt, gr, gd, gl, u_ij, img_ij, r_ij, gamma, dt) %#codegen

    u = zeros(blockSize, blockSize);

    ugt = zeros(blockSize, blockSize);
    ugt(2:blockSize, :) = ug_cur(1:blockSize-1, :);
    if i == 1
        ugt(1, :) = ug_cur(1, :);
    else
        ugt(1, :) = ug_top(blockSize, :);
    end

    ugr = zeros(blockSize, blockSize);
    ugr(:, 2:blockSize) = ug_cur(:, 1:blockSize-1);
    if j == 1
        ugr(:, 1) = ug_cur(:, 1);
    else
        ugr(:, 1) = ug_rig(:, blockSize);
    end

    ugd = zeros(blockSize, blockSize);
    ugd(1:blockSize-1, :) = ug_cur(2:blockSize, :);
    if i == tileRows
        ugd(blockSize, :) = ug_cur(blockSize, :);
    else
        ugd(blockSize, :) = ug_dow(1, :);
    end

    ugl = zeros(blockSize, blockSize);
    ugl(:, 1:blockSize-1) = ug_cur(:, 2:blockSize);
    if j == tileCols
        ugl(:, blockSize) = ug_cur(:, blockSize);
    else
        ugl(:, blockSize) = ug_lef(:, blockSize);
    end

    ugDiff = ugt + ugr + ugd + ugl;
    gDiff = gt + gr + gd + gl;
    numerator = ( u_ij + dt * (ugDiff + gamma * (img_ij .* r_ij)) );
    denominator = ( 1 + dt * (gDiff + gamma) );
    u = numerator ./ denominator;


