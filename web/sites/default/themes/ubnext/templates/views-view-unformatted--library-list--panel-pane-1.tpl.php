<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>

<h2><?php print $view->get_title(); ?></h2>
<ul class="list-unstyled ub-list-of-links">
	<?php foreach ($rows as $id => $row): ?>
	  <li><?php print $row; ?></li>
	<?php endforeach; ?>
</ul>

