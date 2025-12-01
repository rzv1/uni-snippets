package com.org.example.repository;

import com.org.example.domain.Entity;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;

public interface PagingRepository<ID, E extends Entity<ID>> extends Repo<ID, E>{
    Page<E> findAllOnPage(Pageable pageable);
}
